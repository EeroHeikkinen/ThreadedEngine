#include "physics_motion_state.hh"
#include "physics_tree.hh"


PhysicsMotionState::PhysicsMotionState(const btTransform& initialPos, PhysicsComponent* pComponent) :
									  initialPos(initialPos), pComponent(pComponent)
									  {}

void PhysicsMotionState::setComponent(PhysicsComponent* _pComponent) {
	pComponent = _pComponent;
}

void PhysicsMotionState::getWorldTransform(btTransform& worldTrans) const{
	worldTrans = initialPos;
}

void PhysicsMotionState::setWorldTransform(const btTransform& worldTrans){
	pComponent->setTransformation(worldTrans);
}
