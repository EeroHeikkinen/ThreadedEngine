#include "component.hh"
#include "device.hh"

#include <iostream>//TEMP
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;


//RenderComponent

RenderComponent::RenderComponent(void){}

RenderComponent::~RenderComponent(void){}

//PhysicsComponent

PhysicsComponent::PhysicsComponent(btCollisionShape* collisionMesh_,
                                   PhysicsNode* parent_,
								   vec3 initialPos_,
								   mat4& model_,
								   float mass_) :
    collisionMesh(collisionMesh_),
    initialPos(initialPos_),
    model(model_),
    mass(mass_)
    {
        node = DEVICE.getPhysicsThread().getPhysicsTree().addNode(parent_, this);

        btTransform tmp_btInitialPos;
        tmp_btInitialPos.setOrigin(btVector3(initialPos.x, initialPos.y, initialPos.z));

        motionState = new PhysicsMotionState(tmp_btInitialPos, node);

        // WUT IS THIS FALLINERTIA
        btVector3 fallInertia(0,0,0);
        collisionMesh->calculateLocalInertia(mass, fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, motionState,
                                                                 collisionMesh, fallInertia);
        physicsBody = new btRigidBody(fallRigidBodyCI);
        DEVICE.getPhysicsThread().getDynamicsWorld().addRigidBody(physicsBody);
    }

PhysicsComponent::~PhysicsComponent(){
	DEVICE.getPhysicsThread().getPhysicsTree().removeNode(node);
	DEVICE.getPhysicsThread().getDynamicsWorld().removeRigidBody(physicsBody);
	delete collisionMesh;
	delete physicsBody;
	delete motionState;
}

void PhysicsComponent::setTransformation(const btTransform& worldTrans){
	btQuaternion rot = worldTrans.getRotation();
	btVector3 pos = worldTrans.getOrigin();
	quat glm_rot = quat(rot.w(), rot.x(), rot.y(), rot.z());
	model = toMat4(glm_rot) * translate(pos.x(), pos.y(), pos.z());
    std::cout << "TRANSFORMATION";
}

//LogicComponent

LogicComponent::LogicComponent(void) {}

LogicComponent::~LogicComponent(void) {}
