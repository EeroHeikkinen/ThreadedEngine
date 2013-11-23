#include "test_resource_loaders.hh"

#include <iostream>//TEMP


Test::TestResourceLoader::TestResourceLoader(void) {}

Test::TestResourceLoader::~TestResourceLoader(void) {
    delete pCamera;
    delete pTestRenderer;
    delete pSphere;
    delete pBox;
}

void Test::TestResourceLoader::loadResources(void) {
    pSphere = new Test::Sphere(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.7f, 0.0f)));
    pCamera = new Test::Camera();
    pTestRenderer = new Test::TestRenderer(pCamera);
    pBox = new Test::Box(2.0f, 0.1f, 2.0f, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.1f, 0.0f)));

    addRenderer(pTestRenderer);
    addEntity(pSphere);
    addEntity(pBox);
    addEntity(pCamera);
}
