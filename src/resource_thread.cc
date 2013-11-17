#include "resource_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>
#include <iostream>//TEMP


ResourceThread::ResourceThread(Device& device) :
    running(true) {
    thread = std::thread(&ResourceThread::launch, this);
}

ResourceThread::~ResourceThread(void) {
    if (running) {
        running = false;
        thread.join();
    }

    delete pTestRenderer;//TEMP
    delete pCamera;//TEMP
    delete pSphere;//TEMP
    delete pBox;//TEMP
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
    while (!Device::getDevice().isGlewInitialized()) {
        sf::sleep(sf::milliseconds(5));
    }

    //Begin of TEMP
    pCamera = new test::Camera();
    pTestRenderer = new test::TestRenderer(pCamera);

    Device::getDevice().getRenderThread().detachContext();

    pSphere = new test::Sphere(
                               new btSphereShape(1),
                               Device::getDevice().getPhysicsThread().getPhysicsTree()->getRoot(),
                               glm::vec3(0.0f, 2.0f, 0.0f),
                               1.0f
                               );

    pBox = new test::Box(2.0f, 0.1f, 2.0f, glm::vec3(0.0f, -2.0f, 0.0f));

    Device::getDevice().getRenderThread().attachContext();
    //End of TEMP
}

void ResourceThread::loop(void) {
    sf::sleep(sf::milliseconds(250));

    /*
    TODO:
    Improve the delay
    */
}
