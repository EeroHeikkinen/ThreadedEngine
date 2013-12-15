#include "component.hh"
#include "device.hh"
#include "test_renderers.hh"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>


//RenderComponent
void StupidRenderComponent::addToStructure(void){
    pTargetStructure->addComponent(this);
}
void StupidRenderComponent::removeFromStructure(void){
    pTargetStructure->removeComponent(this);
}
void StupidCameraComponent::addToStructure(void){
    pTargetStructure->addComponent(this);
}
void StupidCameraComponent::removeFromStructure(void){
    pTargetStructure->removeComponent(this);
}

//LogicComponent
void LogicComponent::addToStructure(void){
    std::cout << "Adding logic!" << std::endl;
    DEVICE.getLogicThread().addComponent(this);
}
void LogicComponent::removeFromStructure(void){
    std::cout << "Removing logic!" << std::endl;
    DEVICE.getLogicThread().removeComponent(this);
}

//PhysicsComponent
PhysicsComponent::PhysicsComponent(std::unique_ptr<btCollisionShape> _pCollisionMesh,
                                   PhysicsNode* pParent,
								   glm::vec3 initialPos,
								   glm::vec3 initialVel,
								   glm::mat4& model,
								   glm::mat4& scale,
								   float _mass,
								   float _restitution) :
    pCollisionMesh(std::move(_pCollisionMesh)),
    pParent(pParent),
    model(model),
    scale(scale),
    mass(_mass),
    restitution(_restitution),
    motionState(this)
    {
        btVector3 fallInertia = btVector3(0.0f,0.0f,0.0f);
        pCollisionMesh->calculateLocalInertia(mass, fallInertia);
        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,
                                                             &motionState,
                                                             pCollisionMesh.get(),
                                                             fallInertia);
        rigidBodyCI.m_restitution = restitution;
        pPhysicsBody = make_unique<btRigidBody>(rigidBodyCI);
        pPhysicsBody->setLinearVelocity(btVector3(initialVel.x, initialVel.y, initialVel.z));
    }
PhysicsComponent::~PhysicsComponent(void){}

const glm::mat4& PhysicsComponent::getModelMatrix(void){
    return model;
}

void PhysicsComponent::setModelMatrix(const glm::mat4& _model){
    model = _model;
}

const glm::mat4& PhysicsComponent::getScaleMatrix(void){
    return scale;
}

void PhysicsComponent::addToStructure(void){
    pPhysicsNode = std::unique_ptr<PhysicsNode>(DEVICE.getPhysicsThread().getPhysicsTree().addNode(pParent, this));
    DEVICE.getPhysicsThread().getDynamicsWorld().addRigidBody(pPhysicsBody.get());
}

void PhysicsComponent::removeFromStructure(void){
    DEVICE.getPhysicsThread().getPhysicsTree().removeNode(pPhysicsNode.release());
    DEVICE.getPhysicsThread().getDynamicsWorld().removeRigidBody(pPhysicsBody.get());
}
