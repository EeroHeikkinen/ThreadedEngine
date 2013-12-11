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

    for (auto loader : vpResourceLoaders) {
        delete loader;
    }
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
}

void ResourceThread::loop(void){
    while (!qLoadCalls.empty()) {
        std::cout << "a" << std::endl;

        DEVICE.getRenderThread().detachContext();

        ResourceLoadCall call;
        if (qLoadCalls.try_pop(call)) {
            (call.first.first->*call.first.second)(call.second.first, call.second.second);
        }

        DEVICE.getRenderThread().attachContext();
    }

    sf::sleep(sf::milliseconds(10));

    /*
    TODO:
    Improve the delay
    */
}

void ResourceThread::addResourceLoader(ResourceLoader* pResLoader) {
    vpResourceLoaders.push_back(pResLoader);
}

void ResourceThread::pushResourceLoadCall(ResourceLoadCall loadCall) {
    qLoadCalls.push(loadCall);
}
