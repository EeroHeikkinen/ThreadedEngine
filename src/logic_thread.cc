#include "logic_thread.hh"
#include "test_entities.hh"
#include "test_renderers.hh"
#include "device.hh"

#include <SFML/Window.hpp>

namespace Test{class Camera;}


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
    //create a StupidRenderer
    Test::StupidRenderer* pRenderer =
        DEVICE.getRenderThread().addRenderer(
            make_unique<Test::StupidRenderer>());
    //create a camera for the StupidRenderer
    DEVICE.getUniverse().addChild(
        make_unique<Test::Camera>(pRenderer));
    //create a bunch of edwerdz
    Test::EdwerdCollection* edwerdCollection =
        DEVICE.getUniverse().addChild(make_unique<Test::EdwerdCollection>());
    edwerdCollection->loadEdwerds(pRenderer);
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
