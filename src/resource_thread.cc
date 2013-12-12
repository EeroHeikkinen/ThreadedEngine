#include "resource_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>


ResourceThread::ResourceThread(Device* pDevice, unsigned int initOrderNumber) :
    running(true)
    {
        thread = std::thread(&ResourceThread::launch, this, initOrderNumber);
    }

ResourceThread::~ResourceThread(void){
    if (running){
        running = false;
        thread.join();
    }
}

void ResourceThread::launch(unsigned int initOrderNumber){
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
