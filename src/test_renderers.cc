#include "test_renderers.hh"
#include "device.hh"
#include "test_entities.hh"


test::TestRenderer::TestRenderer(test::Camera* pCamera_) :
    sceneGraph(Device::getDevice().getSceneGraph()),
    pCamera(pCamera_) {
    Device::getDevice().getRenderThread().addRenderer(this);
}

test::TestRenderer::~TestRenderer(void) {
    Device::getDevice().getRenderThread().deleteRenderer(this);
}

void test::TestRenderer::render(void) {
    for (auto it = sceneGraph.begin(); it != sceneGraph.end(); it++) {
        (*it)->render(pCamera->getViewMatrix(), pCamera->getProjectionMatrix());
    }
}
