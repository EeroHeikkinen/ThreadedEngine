#include "event_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>
#include <GL/GLEW.h>
#include <SFML/OpenGL.hpp>
#include <iostream> //temp


EventThread::EventThread(Device& device) :
    device(device),
    running(true) {
    thread = std::thread(&EventThread::launch, this);
}

EventThread::~EventThread(void) {
    if (running) {
        running = false;
        thread.join();
    }
}

void EventThread::launch(void) {
    //New thread begins here
    init();
    while (running)
        loop();
}

void EventThread::stop(void) {
    running = false;
}

void EventThread::join(void) {
    thread.join();
}

void EventThread::init(void) {
    std::cout << "Helloes from EventThread!" << std::endl;//temp
}

void EventThread::loop(void) {
    /*// handle events
    sf::Event event;
    while (device.getRenderThread().getWindow().pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            // end the program
            device.stop();
        }
        /*else if (event.type == sf::Event::Resized)
        {
            // adjust the viewport when the window is resized
            glViewport(0, 0, event.size.width, event.size.height);
        }
    }*/
}
