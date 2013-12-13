#include "logic_thread.hh"
#include "test_entities.hh"
#include "test_renderers.hh"
#include "device.hh"

#include <SFML/Window.hpp>

namespace Test{class Camera;}
class StandardResourceLoader;


LogicThread::LogicThread(Device* pDevice, unsigned int initOrderNumber) :
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
        DEVICE.getUniverse().addChild(make_unique<Test::EdwerdCollection>(pRenderer));

    DEVICE.getRenderThread().detachContext();

        DEVICE.getUniverse().addChild(
            make_unique<Test::Box>
                (pRenderer,
                 100.0f,1.0f,100.0f,
                dynamic_cast<StandardResourceLoader*>
                    (DEVICE.getResourceThread().getResourceLoaderPtr(MATERIAL))
                        ->getMaterialPtr("material_grassblock"),
                 glm::vec3(-1.0f,-5.0f,1.0f),
                 glm::vec3(0.0f,0.0f,0.0f),
                 0.0f,
                 0.5f));

        for(int j = -40; j <= 40; j=j+4){
            for(float i = -4.0f; i < 50.0f; i=i+2.05){
                DEVICE.getUniverse().addChild(
                    make_unique<Test::Box>
                        (pRenderer,
                         1.0f,1.0f,1.0f,
                        dynamic_cast<StandardResourceLoader*>
                            (DEVICE.getResourceThread().getResourceLoaderPtr(MATERIAL))
                                ->getMaterialPtr("material_grassblock"),
                         glm::vec3(j,i,0.0f),
                         glm::vec3(0.0f,0.0f,0.0f),
                         1.0f,
                         0.5f));
            }
        }

        DEVICE.getUniverse().addChild(
            make_unique<Test::Sphere>
                (pRenderer,
                 5.0f,
                 dynamic_cast<StandardResourceLoader*>
                    (DEVICE.getResourceThread().getResourceLoaderPtr(MATERIAL))
                        ->getMaterialPtr("material_edwerd"),
                 glm::vec3(-120.0f,3.0f,-30.0f),
                 glm::vec3(75.0f,20.0f,20.0f),
                 80.0f,
                 0.5f));

    DEVICE.getRenderThread().attachContext();
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
