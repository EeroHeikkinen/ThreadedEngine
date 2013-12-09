#include "logic_thread.hh"
#include "device.hh"
#include <iostream> //temp

#include <SFML/Window.hpp>


LogicThread::LogicThread(Device* pDevice, unsigned int initOrderNumber) :
    running(true),
    initOrderNumber(initOrderNumber)
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
    DEVICE.initSequencer.initialize(this, initOrderNumber);
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
}

void LogicThread::loop(void){
    // render
    for(auto pLogicComponent : spLogicComponents){
        pCurrentComponent = pLogicComponent;
        pLogicComponent->logic();
    }
    if(pToBeErased != nullptr){
        spLogicComponents.erase(pToBeErased);
        pToBeErased = nullptr;
    }

    sf::sleep(sf::milliseconds(10));
    /*
        TODO:
        Improve the delay
    */
}

void LogicThread::addComponent(LogicComponent* pComponent){
    spLogicComponents.insert(pComponent);
}
void LogicThread::removeComponent(LogicComponent* pComponent){
    if(pToBeErased != nullptr){
        spLogicComponents.erase(pToBeErased);
        pToBeErased = nullptr;
    }

    if(pComponent == pCurrentComponent)
        pToBeErased = pComponent;
    else
        spLogicComponents.erase(pComponent);
}


/*void LogicThread::addLogicComponents(tbb::concurrent_vector<LogicComponent*>& vpComponents){
    for(auto pComponent : vpComponents)
        vpLogicComponents.push_back(pComponent);
}*/

/*void LogicThread::deleteLogicComponent(LogicComponent* pLogicComponent){
    for (auto it = vpLogicComponents.begin(); it != vpLogicComponents.end(); it++){
        if (*it == pLogicComponent){
            vpLogicComponents.erase(it);
            return;
        }
    }
}*/
