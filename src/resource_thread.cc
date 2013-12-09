#include "resource_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>


ResourceThread::ResourceThread(Device* pDevice, unsigned int initOrderNumber) :
    running(true),
    initOrderNumber(initOrderNumber)
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
    DEVICE.initSequencer.initialize(this, initOrderNumber);
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
    sf::sleep(sf::milliseconds(250));

    /*
    TODO:
    Improve the delay
    */
}
