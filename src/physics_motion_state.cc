#include "physics_motion_state.hh"
#include "physics_tree.hh"


PhysicsMotionState::PhysicsMotionState(const btTransform& initialPos_, PhysicsComponent* component_) :
									  initialPos(initialPos_), component(component_)
									  {}

void PhysicsMotionState::setComponent(PhysicsComponent* component_) {
	component = component_;
}

void PhysicsMotionState::getWorldTransform(btTransform& worldTrans) const{
	worldTrans = initialPos;
}

void PhysicsMotionState::setWorldTransform(const btTransform& worldTrans) {
	if (component == nullptr)
		return;
	component->setTransformation(worldTrans);
}
