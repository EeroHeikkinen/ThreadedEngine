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
    while(!qLoadCalls.empty()){
        std::cout << "a" << std::endl;

        DEVICE.getRenderThread().detachContext();

            ResourceLoadCall call;
            if (qLoadCalls.try_pop(call))
                call.pResLoader->load(call.resType, call.resId);

        DEVICE.getRenderThread().attachContext();
    }

    sf::sleep(sf::milliseconds(10));

    /*
    TODO:
    Improve the delay
    */
}

void ResourceThread::addResourceLoader(std::unique_ptr<ResourceLoader> pLoader,
                                       std::vector<ResourceType> vTypes){
    for(ResourceType type : vTypes)
        mpResourceLoadersByType[type] = pLoader.get();

    lpResourceLoaders.emplace_front(std::move(pLoader));
}

void ResourceThread::loadResource(ResourceType resType, const std::string& resId){
    auto it = mpResourceLoadersByType.find(resType);
    if(it != mpResourceLoadersByType.end()){
        ResourceLoadCall call = {it->second, resType, resId};
        qLoadCalls.push(call);
    }
    else{/* TODO: throw an exception */}
}
