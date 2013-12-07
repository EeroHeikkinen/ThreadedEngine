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

	btMatrix3x3 B = worldTrans.getBasis();
	btVector3 O = worldTrans.getOrigin();
	// std::cout << "Component: " << component << std::endl << std::endl;
	// std::cout << "Basis: " << std::endl;
	// for(size_t i = 0; i < 3; ++i){
 //        for(size_t j = 0; j < 3; ++j)
 //            std::cout << B[i][j] << " ";
 //        std::cout << std::endl;
	// }
	// std::cout << std::endl;
	// std::cout << "Origin: ";
    // for(size_t i = 0; i < 3; ++i)
    //     std::cout << O[i] << " ";
    // std::cout << std::endl << std::endl;
	component->setTransformation(worldTrans);
}
