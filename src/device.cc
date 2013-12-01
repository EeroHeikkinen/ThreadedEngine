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

void Device::setGlewInitialized(bool glewInitialized_){
    glewInitialized = glewInitialized_;
}

bool Device::isGlewInitialized(void) const{
    return glewInitialized;
}

RenderThread& Device::getRenderThread(void){
    return renderThread;
}

LogicThread& Device::getLogicThread(void){
    return logicThread;
}

PhysicsThread& Device::getPhysicsThread(void){
    return physicsThread;
}

SceneGraph& Device::getSceneGraph(void){
    return sceneGraph;
}

Device::Device(void) :
    initThreadID(0),
    glewInitialized(false),
    running(true),
    renderThread(*this),
    logicThread(*this),
    physicsThread(*this),
    resourceThread(*this)
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
