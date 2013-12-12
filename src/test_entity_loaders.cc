#include "test_entity_loaders.hh"
#include "device.hh"
#include "resource_loader.hh"

#include <stdlib.h>
#include <time.h>
#include <SFML/Window.hpp>


Test::TestEntityLoader::TestEntityLoader(void) {}

Test::TestEntityLoader::~TestEntityLoader(void) {
    delete pCamera;
    delete pTestRenderer;
    //delete pBox;

    delete pTexture;
    delete pShader;
    delete pMaterial;
    delete pMesh;

    for (auto pEdwerd : vpEdwerdz) {
        delete pEdwerd;
    }
}

void Test::TestEntityLoader::loadEntities(void) {
    srand(time(NULL));

    pCamera = new Test::Camera();
    pTestRenderer = new Test::TestRenderer(pCamera);
    //pBox = new Test::Box(2.0f, 0.1f, 2.0f, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.1f, 0.0f)));

    addRenderer(pTestRenderer);
    //addEntity(pBox);
    addEntity(pCamera);

    sf::sleep(sf::milliseconds(300));

    StandardResourceLoader* pResLoader =
        dynamic_cast<StandardResourceLoader*>(DEVICE.getResourceThread().getResourceLoaderPtr(MESH));

    pMesh = pResLoader->getMeshPtr("sphere");
    pMaterial = pResLoader->getMaterialPtr("material_edwerd");
    if (pMesh == nullptr || pMaterial == nullptr)
        std::cout << "NULLIA TULEE SAATANAVITTU!!1" << std::endl;

    for (int i = 0; i < 100; i++) {
        Test::Edwerd* pEdwerd =
            new Test::Edwerd(pMesh, pMaterial,
                glm::translate(glm::mat4(1.0f),
                    glm::vec3(50.0f-(rand()%10000)/100.0f,
                              50.0f-(rand()%10000)/100.0f,
                              50.0f-(rand()%10000)/100.0f)));
        addEntity(pEdwerd);
        vpEdwerdz.push_back(pEdwerd);
    }
}
