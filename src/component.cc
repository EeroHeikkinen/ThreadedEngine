#include "component.hh"
#include "device.hh"

#include <iostream>//TEMP
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;


void StupidRenderComponent::addToStructure(void){}



//PhysicsComponent
PhysicsComponent::PhysicsComponent(std::unique_ptr<btCollisionShape> _pCollisionMesh,
                                   PhysicsNode* pParent,
								   vec3 _initialPos,
								   vec3 _initialVel,
								   mat4& model,
								   float mass,
								   float restitution) :
    pCollisionMesh(std::move(_pCollisionMesh)),
    pParent(pParent),
    initialPos(std::move(_initialPos)),
    initialVel(std::move(_initialVel)),
    model(model),
    mass(mass),
    restitution(restitution)
    {
        btTransform btInitialPos(btQuaternion(0,0,0,1),
                                     btVector3(initialPos.x, initialPos.y, initialPos.z));

        pMotionState = make_unique<PhysicsMotionState>(btInitialPos, this);

        btVector3 fallInertia = btVector3(0.0f,0.0f,0.0f);
        pCollisionMesh->calculateLocalInertia(btScalar(mass), fallInertia);
        btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass,
                                                             pMotionState.get(),
                                                             pCollisionMesh.get(),
                                                             fallInertia);
        pPhysicsBody = make_unique<btRigidBody>(RigidBodyCI);
        pPhysicsBody->setRestitution(restitution);
    }

PhysicsComponent::~PhysicsComponent(){
    DEVICE.getPhysicsThread().getDynamicsWorld().removeRigidBody(pPhysicsBody.get());
}

void PhysicsComponent::addToStructure(void){
    pPhysicsNode = std::unique_ptr<PhysicsNode>(DEVICE.getPhysicsThread().getPhysicsTree().addNode(pParent, this));
    DEVICE.getPhysicsThread().getDynamicsWorld().addRigidBody(pPhysicsBody.get());
}

void PhysicsComponent::removeFromStructure(void){
    DEVICE.getPhysicsThread().getDynamicsWorld().removeRigidBody(pPhysicsBody.get());
}

void PhysicsComponent::setTransformation(const btTransform& worldTrans){
	btQuaternion rot = worldTrans.getRotation();
	btVector3 pos = worldTrans.getOrigin();
	quat glm_rot = quat(rot.w(), rot.x(), rot.y(), rot.z());

	model = translate(pos.x(), pos.y(), pos.z()) * toMat4(glm_rot);

    //std::cout << pos.x() << std::endl << pos.y() << std::endl << pos.z() << std::endl << std::endl;
}
