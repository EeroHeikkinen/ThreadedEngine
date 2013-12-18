#include "logic_thread.hh"
#include "test_entities.hh"
#include "test_renderers.hh"
#include "device.hh"

namespace Test{class Camera;}
class StandardResourceLoader;


LogicThread::LogicThread(Device* pDevice, unsigned int initOrderNumber) :
    device(*pDevice),
    running(true)
    {
        thread = std::thread(&LogicThread::launch, this, initOrderNumber);
    }

LogicThread::~LogicThread(void){
    if (running){
        running = false;
        thread.join();
    }
}

void LogicThread::launch(unsigned int initOrderNumber){
    //New thread begins here
    device.initSequencer.initialize(this, initOrderNumber);
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
        device.getRenderThread().addRenderer(
            make_unique<Test::StupidRenderer>());
    device.getUniverse().addChild(
        make_unique<Test::World>(pRenderer));
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
