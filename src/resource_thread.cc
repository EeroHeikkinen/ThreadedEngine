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
    std::lock_guard<std::mutex> initLock(Device::getDevice().initMutex);
    std::cout << "ResInitBegin" << std::endl; //temp

    while (!Device::getDevice().isGlewInitialized())
        sf::sleep(sf::milliseconds(5));

    //Begin of TEMP
    Device::getDevice().getRenderThread().detachContext();

    testResLoader = new Test::TestResourceLoader();
    testResLoader->loadResources();
    testResLoader->pushResources();

    Device::getDevice().getRenderThread().attachContext();
    //End of TEMP
    std::cout << "ResInitEnd" << std::endl; //temp
}

void ResourceThread::loop(void){
    sf::sleep(sf::milliseconds(250));

    /*
    TODO:
    Improve the delay
    */
}
