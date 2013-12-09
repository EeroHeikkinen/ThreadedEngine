#include "test_renderers.hh"
#include "device.hh"
#include "test_entities.hh"

Test::StupidRenderer::StupidRenderer(void) :
    defaultCamera(makeStupidCameraComponent

void Test::StupidRenderer::render(void){
    for(auto pRenderComponent : spRenderComponents)
        pRenderComponent->render(pCamera->getViewMatrix(),
                                 pCamera->getProjMatrix());
}



Test::TestRenderer::TestRenderer(Test::Camera* pCamera_) :
    sceneGraph(DEVICE.getSceneGraph()),
    pCamera(pCamera_)
    {}

Test::TestRenderer::~TestRenderer(void){}

void Test::TestRenderer::render(void){
    for (auto it = sceneGraph.begin(); it != sceneGraph.end(); it++) {
        (*it)->render(pCamera->getViewMatrix(), pCamera->getProjMatrix());
    }
}
