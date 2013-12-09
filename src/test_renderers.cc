#include "test_renderers.hh"
#include "device.hh"
#include "test_entities.hh"

Test::StupidRenderer::StupidRenderer(void) :
    defaultView(glm::lookAt(glm::vec3(5.0f,2.0f,0.0f),
                            glm::vec3(0.0f,0.0f,0.0f),
                            glm::vec3(0.0f,1.0f,0.0f))),
    defaultProj(glm::perspective(60.0f, //FoV
                                 4.0f/3.0f, //Aspect ratio
                                 0.1f, //near CP
                                 100.0f)), //far CP
    defaultCamera(StupidCameraComponent(this, defaultView, defaultProj)),
    pCurrentCamera(&defaultCamera)
    {}

void Test::StupidRenderer::render(void){
    std::lock_guard<std::mutex> lock(mutex);
    for(auto pStupidRenderComponent : spStupidRenderComponents)
        pStupidRenderComponent->render(pCurrentCamera->getViewMatrix(),
                                 pCurrentCamera->getProjMatrix());
}

void Test::StupidRenderer::addComponent(StupidRenderComponent* stupidRenderComponent){
    spStupidRenderComponents.insert(stupidRenderComponent);
}
void Test::StupidRenderer::removeComponent(StupidRenderComponent* stupidRenderComponent){
    std::lock_guard<std::mutex> lock(mutex);
    spStupidRenderComponents.unsafe_erase(stupidRenderComponent);
}

void Test::StupidRenderer::addComponent(StupidCameraComponent* stupidCameraComponent){
    std::lock_guard<std::mutex> lock(mutex);
    pCurrentCamera = stupidCameraComponent;
}
void Test::StupidRenderer::removeComponent(StupidCameraComponent* stupidCameraComponent){
    std::lock_guard<std::mutex> lock(mutex);
    pCurrentCamera = &defaultCamera;
}
