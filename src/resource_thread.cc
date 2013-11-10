#include "resource_thread.hh"

#include <iostream> //temp


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
    std::cout << "Helloes from ResourceThread!" << std::endl;//temp
}

void ResourceThread::loop(void) {
    std::cout << "resource ";//temp
}
