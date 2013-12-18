#include "device.hh"

#include <SFML/OpenGL.hpp>


Device& Device::getDevice(void){
    static Device device; // singleton instance
    return device;
}

void Device::stop(void){
    resourceThread.stop();
    logicThread.stop();
    physicsThread.stop();

    resourceThread.join();
    logicThread.join();
    physicsThread.join();

    renderThread.stop();
    running = false;
}

void Device::join(void){
    renderThread.join();
    //sf::Window* pWindow = renderThread.getWindowPtr();
    sf::Window& window = glContextMutex.getWindow();
    if(glContextMutex.getWaitingThreads())
        throw "Destruction failure: threads waiting for GL context";
    else
        window.setActive(true);
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

Entity& Device::getUniverse(void){
    return universe;
}

Device::Device(void) :
    running(true),
    renderThread(this, 1),
    physicsThread(this, 2),
    resourceThread(this, 3),
    logicThread(this, 4)
    {}

void Device::eventLoop(void){
    while (running){
        sf::Window& window = glContextMutex.getWindow();
        //renderThread.getWindowPtr();

        if (window.isOpen()){
            // handle events
            sf::Event event;
            while (window.pollEvent(event)){
                if(event.type == sf::Event::Closed)
                    stop();
                if(event.type == sf::Event::Resized)
                    glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        sf::sleep(sf::milliseconds(10));
    }
}
