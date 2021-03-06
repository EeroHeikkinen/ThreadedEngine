#include "test_renderers.hh"

#include <glm/gtx/transform.hpp>


Test::StupidRenderer::StupidRenderer(void) :
    defaultView(glm::lookAt(glm::vec3(5.0f,2.0f,0.0f),
                            glm::vec3(0.0f,0.0f,0.0f),
                            glm::vec3(0.0f,1.0f,0.0f))),
    defaultProj(glm::perspective(60.0f,     //FoV
                                 4.0f/3.0f, //Aspect ratio
                                 0.1f,      //near CP
                                 100.0f)),  //far CP
    defaultCamera(this, defaultView, defaultProj),
    pCurrentCamera(&defaultCamera)
    {}

void Test::StupidRenderer::render(void){
    std::lock_guard<std::mutex> lock(mutex);
    for(auto pStupidRenderComponent : spStupidRenderComponents)
        pStupidRenderComponent->render(pCurrentCamera->getViewMatrix(),
                                       pCurrentCamera->getProjMatrix());
}

void Test::StupidRenderer::addComponent(StupidRenderComponent* pStupidRenderComponent){
    spStupidRenderComponents.insert(pStupidRenderComponent);
}
void Test::StupidRenderer::removeComponent(StupidRenderComponent* pStupidRenderComponent){
    std::lock_guard<std::mutex> lock(mutex);
    spStupidRenderComponents.unsafe_erase(pStupidRenderComponent);
}

void Test::StupidRenderer::addComponent(StupidCameraComponent* pStupidCameraComponent){
    std::lock_guard<std::mutex> lock(mutex);
    pCurrentCamera = pStupidCameraComponent;
}
void Test::StupidRenderer::removeComponent(StupidCameraComponent* pStupidCameraComponent){
    if(pStupidCameraComponent == pCurrentCamera){
        std::lock_guard<std::mutex> lock(mutex);
        pCurrentCamera = &defaultCamera;
    }
}
