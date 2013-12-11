#include "test_entity_loaders.hh"
#include "resource_loader.hh"
#include "test_models.hh"

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

    for (auto it = vpSingleMeshEntities.begin(); it != vpSingleMeshEntities.end(); it++) {
        delete *it;
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

    // resources
    StandardResourceLoader* pResLoader = new StandardResourceLoader();
    pResLoader->setTextureInfo("edwerd", "res/textures/edwerd.png",
                               Texture::Type::IMG,
                               GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR,
                               GL_WRAP_BORDER, GL_WRAP_BORDER, 4);

    pResLoader->setShaderObjectInfo("VS_texture_normal", "res/shaders/VS_texture_normal.glsl",
                                    GL_VERTEX_SHADER);
    pResLoader->setShaderObjectInfo("FS_texture_normal", "res/shaders/FS_texture_normal.glsl",
                                    GL_FRAGMENT_SHADER);
    pResLoader->setShaderProgramInfo("texture_normal",
                                     std::vector<std::string> {"VS_texture_normal",
                                                               "FS_texture_normal"});

    pResLoader->setMaterialInfo("material_edwerd",
                                std::unordered_map<GLenum, std::string>
                                    {std::make_pair(GL_TEXTURE0, "edwerd")},
                                "texture_normal");

    pResLoader->setMeshInfo("sphere", "material_edwerd");

    pResLoader->loadResource(MESH, "sphere");

    sf::sleep(sf::milliseconds(300));

    pMesh = pResLoader->getMeshPtr("sphere");
    if (pMesh == nullptr)
        std::cout << "NULLIA TULEE SAATANAVITTU!!1" << std::endl;


    for (int i = 0; i < 100; i++) {
        Test::SingleMeshEntity* pSingleMeshEntity =
            new Test::SingleMeshEntity(pMesh,
                glm::translate(glm::mat4(1.0f),
                    glm::vec3(50.0f-(rand()%10000)/100.0f,
                              50.0f-(rand()%10000)/100.0f,
                              50.0f-(rand()%10000)/100.0f)));
        addEntity(pSingleMeshEntity);
        vpSingleMeshEntities.push_back(pSingleMeshEntity);
    }
}
