#include "resource_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>
#include <iostream>//TEMP


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

    delete testResLoader;
}

void ResourceThread::launch(void){
    //New thread begins here
    DEVICE.initSequencer.initialize(this, 3);
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
    while (!DEVICE.isGlewInitialized())
        sf::sleep(sf::milliseconds(5));

    //Begin of TEMP
    DEVICE.getRenderThread().detachContext();

    testResLoader = new Test::TestResourceLoader();
    testResLoader->loadResources();
    testResLoader->pushResources();

    DEVICE.getRenderThread().attachContext();
    //End of TEMP
}

void ResourceThread::loop(void){
    sf::sleep(sf::milliseconds(250));

    /*
    TODO:
    Improve the delay
    */
}
