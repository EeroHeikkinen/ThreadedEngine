#include "component.hh"
#include "device.hh"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;




RenderComponent::RenderComponent(void) {
    //add the component to the render thread
    Device::getDevice().getSceneGraph().addRenderComponent(this);
}

RenderComponent::~RenderComponent(void) {
    //delete the component from the render thread
    Device::getDevice().getSceneGraph().deleteRenderComponent(this);
}


PhysicsComponent::PhysicsComponent(btCollisionShape* collisionMesh_, PhysicsNode* parent,
								   vec3 pos, float mass_) : collisionMesh(collisionMesh_),
								   initial_pos(pos), mass(mass_) {
	node = Device::getDevice().getPhysicsThread().getPhysicsTree()->addNode(parent, this);

	btTransform tmp_initpos;
	tmp_initpos.setOrigin(btVector3(initial_pos.x, initial_pos.y, initial_pos.z));

	motionState = new PhysicsMotionState(tmp_initpos, node);

	// WUT IS THIS FALLINERTIA
	btVector3 fallInertia(0,0,0);
	collisionMesh->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, motionState,
															collisionMesh, fallInertia);
	physicsBody = new btRigidBody(fallRigidBodyCI);
	Device::getDevice().getPhysicsThread().getDynamicsWorld()->addRigidBody(physicsBody);

}

PhysicsComponent::~PhysicsComponent() {

	Device::getDevice().getPhysicsThread().getPhysicsTree()->removeNode(node);

	delete collisionMesh;
	delete physicsBody;
	delete motionState;
	delete node;

}

void PhysicsComponent::setTransformation(const btTransform& worldTrans) {
	btQuaternion rot = worldTrans.getRotation();
	btVector3 pos = worldTrans.getOrigin();
	quat glm_rot = quat(rot.w(), rot.x(), rot.y(), rot.z());
	to_world = toMat4(glm_rot);
	mat4 translation = translate(pos.x(), pos.y(), pos.z());
	
	to_world = to_world * translation;

}

LogicComponent::LogicComponent(void) {
    //add the component to the logic thread
    Device::getDevice().getLogicThread().addLogicComponent(this);
}

LogicComponent::~LogicComponent(void) {
    //delete the component from the logic thread
    Device::getDevice().getLogicThread().deleteLogicComponent(this);
}
