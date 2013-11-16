#include "component.hh"
#include "device.hh"

#include <iostream>//TEMP


RenderComponent::RenderComponent(void) {
    //add the component to the render thread
    Device::getDevice().getRenderThread().addRenderComponent(this);
}

RenderComponent::~RenderComponent(void) {
    //delete the component from the render thread
    Device::getDevice().getRenderThread().deleteRenderComponent(this);
}


LogicComponent::LogicComponent(void) {
    //add the component to the logic thread
    Device::getDevice().getLogicThread().addLogicComponent(this);
}

LogicComponent::~LogicComponent(void) {
    //delete the component from the logic thread
    Device::getDevice().getLogicThread().deleteLogicComponent(this);
}


void PhysicsComponent::calculate(void) {
	std::cout << "calculating... YEAH" << std::endl;//TEMP
}

