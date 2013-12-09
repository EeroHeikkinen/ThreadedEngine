#include "physics_motion_state.hh"
#include "physics_tree.hh"
#include <iostream> //temp

//TEMP
#include <iostream>


PhysicsMotionState::PhysicsMotionState(const btTransform& initialPos_, PhysicsComponent* component_) :
									  initialPos(initialPos_), component(component_)
									  {std::cout << "MotStatArgh: " << component << std::endl;}

void PhysicsMotionState::setComponent(PhysicsComponent* component_) {
	component = component_;
}

void PhysicsMotionState::getWorldTransform(btTransform& worldTrans) const{
	worldTrans = initialPos;
}

void PhysicsMotionState::setWorldTransform(const btTransform& worldTrans){
	component->setTransformation(worldTrans);
}
