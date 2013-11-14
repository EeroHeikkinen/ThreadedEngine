#include "component.hh"
#include <iostream>

RenderComponent::RenderComponent(void) { }

RenderComponent::~RenderComponent(void) { }

void RenderComponent::render(void) { }


PhysicsComponent::PhysicsComponent() { }

PhysicsComponent::~PhysicsComponent() { }

void PhysicsComponent::calculate() { 
	std::cout << "calculating... YEAH" << std::endl;
}

