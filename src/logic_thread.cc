#include "logic_thread.hh"
#include "device.hh"
#include <iostream> //temp

#include <SFML/Window.hpp>


LogicThread::LogicThread(Device& device_) :
    running(true)
    {
        thread = std::thread(&LogicThread::launch, this);
    }

LogicThread::~LogicThread(void){
    if (running){
        running = false;
        thread.join();
    }
}

void LogicThread::launch(void){
    //New thread begins here
    init();
    while (running)
        loop();
}

void LogicThread::stop(void){
    running = false;
}

void LogicThread::join(void){
    thread.join();
}

void LogicThread::init(void){
    { // init mutex
        std::unique_lock<std::mutex> initLock(DEVICE.initMutex);
        DEVICE.initCV.wait(initLock, []{ return DEVICE.initThreadID == 1; });
    }

    std::cout << "LogicInit" << std::endl; //temp

    { // notify other threads
        std::lock_guard<std::mutex> initLock(DEVICE.initMutex);
        DEVICE.initThreadID = 2;
        DEVICE.initCV.notify_one();
    }
}

void LogicThread::loop(void){
    // render
    for (auto it = vpLogicComponents.begin(); it != vpLogicComponents.end(); it++)
        (*it)->logic();

    sf::sleep(sf::milliseconds(10));
    /*
        TODO:
        Improve the delay
    */
}

void LogicThread::addLogicComponent(LogicComponent* pComponent){
    vpLogicComponents.push_back(pComponent);
}

void LogicThread::addLogicComponents(tbb::concurrent_vector<LogicComponent*>& vpComponents){
    for (auto it = vpComponents.begin(); it != vpComponents.end(); it++) {
        vpLogicComponents.push_back(*it);
    }
}

/*void LogicThread::deleteLogicComponent(LogicComponent* pLogicComponent){
    for (auto it = vpLogicComponents.begin(); it != vpLogicComponents.end(); it++){
        if (*it == pLogicComponent){
            vpLogicComponents.erase(it);
            return;
        }
    }
}*/
