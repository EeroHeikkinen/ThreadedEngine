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

    delete testEntLoader;//temp
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

    testResLoader->loadFromTXT("res/test_res_list.txt");

    testEntLoader = new Test::TestEntityLoader();
    testEntLoader->loadEntities();
    testEntLoader->pushEntities();

    DEVICE.getRenderThread().attachContext();

    //End of TEMP
}

void ResourceThread::loop(void){
    while (!qLoadCalls.empty()) {
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
