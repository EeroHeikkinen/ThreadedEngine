#include "device.hh"

#include <SFML/OpenGL.hpp>
#include <iostream>//TEMP


Device& Device::getDevice(void){
    static Device device; // singleton instance
    return device;
}

void Device::stop(void){
    renderThread.stop();
    logicThread.stop();
    physicsThread.stop();
    resourceThread.stop();
    running = false;
}

void Device::join(void){
    renderThread.join();
    physicsThread.join();
    logicThread.join();
    resourceThread.join();
}

RenderThread& Device::getRenderThread(void){
    return renderThread;
}

PhysicsThread& Device::getPhysicsThread(void){
    return physicsThread;
}

ResourceThread& Device::getResourceThread(void){
    return resourceThread;
}

LogicThread& Device::getLogicThread(void){
    return logicThread;
}

SceneGraph& Device::getSceneGraph(void){
    return sceneGraph;
}

Device::Device(void) :
    running(true),
    renderThread(*this),
    physicsThread(*this),
    resourceThread(*this),
    logicThread(*this)
    {}

void Device::eventLoop(void){
    while (running){
        sf::Window* pWindow = renderThread.getWindowPtr();

        if (pWindow->isOpen()){
            if (renderThread.isWindowInitialized()){
                // handle events
                sf::Event event;
                while (pWindow->pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        // end the program
                        stop();
                    }
                    else if (event.type == sf::Event::Resized){
                        // adjust the viewport when the window is resized
                        glViewport(0, 0, event.size.width, event.size.height);
                    }
                }
            }
        }

        sf::sleep(sf::milliseconds(10));
    }
}
