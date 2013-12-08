#include "component.hh"
#include "device.hh"

#include <iostream>//TEMP
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;


//PhysicsComponent
PhysicsComponent::PhysicsComponent(std::unique_ptr<btCollisionShape> _pCollisionMesh,
                                   PhysicsNode* pParent,
								   vec3 initialPos,
								   vec3 initialVel,
								   mat4& model,
								   float mass,
								   float restitution) :
    pCollisionMesh(std::move(_pCollisionMesh)),
    initialPos(initialPos),
    model(model),
    mass(mass)
    {
        node = DEVICE.getPhysicsThread().getPhysicsTree().addNode(pParent, this);
        btTransform btInitialPos(btQuaternion(0,0,0,1),
                                     btVector3(initialPos.x, initialPos.y, initialPos.z));

        pMotionState = make_unique<PhysicsMotionState>(btInitialPos, this);

        btVector3 fallInertia = btVector3(0.0f,0.0f,0.0f);
        pCollisionMesh->calculateLocalInertia(btScalar(mass), fallInertia);
        btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass,
                                                             pMotionState,
                                                             pCollisionMesh,
                                                             fallInertia);
        pPhysicsBody = make_unique<btRigidBody>(RigidBodyCI);
        pPhysicsBody->setRestitution(restitution);

        //to be moved elsewhere
        DEVICE.getPhysicsThread().getDynamicsWorld().addRigidBody(physicsBody);
    }

PhysicsComponent::~PhysicsComponent(){
	delete node;
    DEVICE.getPhysicsThread().getDynamicsWorld().removeRigidBody(physicsBody);
	delete collisionMesh;
	delete physicsBody;
	delete motionState;
}

void PhysicsComponent::addToStructure(void){
    node = DEVICE.getPhysicsThread().getPhysicsTree().addNode(pParent, this);
    DEVICE.getPhysicsThread().getDynamicsWorld().addRigidBody(physicsBody);

void PhysicsComponent::setTransformation(const btTransform& worldTrans){
	btQuaternion rot = worldTrans.getRotation();
	btVector3 pos = worldTrans.getOrigin();
	quat glm_rot = quat(rot.w(), rot.x(), rot.y(), rot.z());

	model = translate(pos.x(), pos.y(), pos.z()) * toMat4(glm_rot);

    //std::cout << pos.x() << std::endl << pos.y() << std::endl << pos.z() << std::endl << std::endl;
}

//LogicComponent

LogicComponent::LogicComponent(void) {}

LogicComponent::~LogicComponent(void) {}
