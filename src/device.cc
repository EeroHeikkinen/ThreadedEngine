#include "device.hh"
#include <SFML/OpenGL.hpp>
#include <iostream> //temp


Device::Device(void) :
    renderThread(*this),
    eventThread(*this),
    physicsThread(*this),
    running(true) {
    eventLoop();
}

void Device::join(void) {
    renderThread.join();
    physicsThread.join();
}

void Device::stop(void) {
    renderThread.stop();
    physicsThread.stop();
    running = false;
}

RenderThread& Device::getRenderThread(void) {
    return renderThread;
}

void Device::eventLoop(void) {
    while (running) {
        sf::Window* pWindow = renderThread.getWindowPtr();

        if (pWindow->isOpen()) {
            if (renderThread.isWindowInitialized()) {
                // handle events
                sf::Event event;
                while (pWindow->pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        // end the program
                        stop();
                    }
                    else if (event.type == sf::Event::Resized)
                    {
                        // adjust the viewport when the window is resized
                        glViewport(0, 0, event.size.width, event.size.height);
                    }
                }
            }
        }

        sf::sleep(sf::milliseconds(10));
    }
}
