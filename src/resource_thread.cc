#include "resource_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>
#include <iostream>//TEMP


ResourceThread::ResourceThread(Device& device) :
    device(device),
    running(true) {
    thread = std::thread(&ResourceThread::launch, this);
}

ResourceThread::~ResourceThread(void) {
    if (running) {
        running = false;
        thread.join();
    }

    delete pTriangle;//TEMP
}

void ResourceThread::launch(void) {
    //New thread begins here
    init();
    while (running)
        loop();
}

void ResourceThread::stop(void) {
    running = false;
}

void ResourceThread::join(void) {
    thread.join();
}

void ResourceThread::init(void) {
    while (!device.isGlewInitialized()) {
        sf::sleep(sf::milliseconds(5));
    }

    Device::getDevice().getRenderThread().detachContext();
    pTriangle = new test::Triangle();//TEMP
    Device::getDevice().getRenderThread().attachContext();
}

void ResourceThread::loop(void) {
    sf::sleep(sf::milliseconds(250));

    /*
    TODO:
    Improve the delay
    */
}
