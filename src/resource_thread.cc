#include "resource_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>
#include <iostream>//TEMP
#include <glm/glm.hpp>//TEMP


ResourceThread::ResourceThread(Device& device_) :
    running(true)
    {
        thread = std::thread(&ResourceThread::launch, this);
    }

ResourceThread::~ResourceThread(void){
    if (running){
        running = false;
        thread.join();
    }

    delete pTestRenderer;//TEMP
    delete pCamera;//TEMP
    delete pSphere;//TEMP
    delete pBox;//TEMP
}

void ResourceThread::launch(void){
    //New thread begins here
    init();
    while (running)
        loop();
}

void ResourceThread::stop(void){
    running = false;
}

void ResourceThread::join(void){
    thread.join();
}

void ResourceThread::init(void){
    while (!Device::getDevice().isGlewInitialized())
        sf::sleep(sf::milliseconds(5));

    //Begin of TEMP
    Device::getDevice().getRenderThread().detachContext();

    auto root = Device::getDevice().getPhysicsThread().getPhysicsTree().getRoot();

    pSphere = new Test::Sphere(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.7f, 0.0f)));
    pCamera = new Test::Camera();
    pTestRenderer = new Test::TestRenderer(pCamera);
    pBox = new Test::Box(2.0f, 0.1f, 2.0f, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.1f, 0.0f)));

    Device::getDevice().getRenderThread().attachContext();
    //End of TEMP
}

void ResourceThread::loop(void){
    sf::sleep(sf::milliseconds(250));

    /*
    TODO:
    Improve the delay
    */
}
