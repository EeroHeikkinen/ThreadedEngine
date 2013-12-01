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
    Device::getDevice().initSequencer.logicThread(this, &LogicThread::init);
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
    std::cout << "LogicInit" << std::endl; //temp
}

void LogicThread::loop(void){
    // render
    for(auto pLogicComponent : vpLogicComponents)
        pLogicComponent->logic();

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
    for(auto pComponent : vpComponents)
        vpLogicComponents.push_back(pComponent);
}

/*void LogicThread::deleteLogicComponent(LogicComponent* pLogicComponent){
    for (auto it = vpLogicComponents.begin(); it != vpLogicComponents.end(); it++){
        if (*it == pLogicComponent){
            vpLogicComponents.erase(it);
            return;
        }
    }
}*/
