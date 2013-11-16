#include "physics_motion_state.hh"
#include "physics_tree.hh"

PhysicsMotionState::PhysicsMotionState(const btTransform& initialpos, PhysicsNode* node_) :
									  initPos(initialpos), node(node_) {}

void PhysicsMotionState::setNode(PhysicsNode* node_) {
	node = node_;
}

void PhysicsMotionState::getWorldTransform(btTransform& worldTrans) const {
	worldTrans = initPos;
}

void PhysicsMotionState::setWorldTransform(const btTransform& worldTrans) {
	if (node == nullptr)
		return;
	node->getComponent()->setTransformation(worldTrans);
}