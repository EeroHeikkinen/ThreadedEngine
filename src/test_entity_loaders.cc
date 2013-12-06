#include "test_entity_loaders.hh"
#include "texture.hh"
#include "shader.hh"
#include "material.hh"
#include "mesh.hh"
#include "test_models.hh"

#include <stdlib.h>
#include <time.h>


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
    pTexture = new Texture(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_WRAP_BORDER, GL_WRAP_BORDER, 4);
    pTexture->loadFromFile("res/textures/edwerd.png");

    pShader = new Shader();
    pShader->addShaderObject(GL_VERTEX_SHADER, "shaders/VS_texture_normal.glsl");
    pShader->addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_texture_normal.glsl");
    pShader->link();

    pMaterial = new Material(GL_TEXTURE0, pTexture, pShader, "MVP");

    pMesh = new Mesh(pMaterial);
    makeUVSphere(pMesh->getVBO(), pMesh->getIBO(), pMesh->getVAO(), pMesh->getNIndices(), 32, 16);
    /*
    TODO
    fix this interface
    */


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
