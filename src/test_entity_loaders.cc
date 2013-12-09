#include "test_entity_loaders.hh"
#include "test_renderers.hh"
#include "test_entities.hh"
#include "texture.hh"
#include "shader.hh"
#include "material.hh"
#include "mesh.hh"
#include "test_models.hh"
#include "device.hh"

#include <stdlib.h>
#include <time.h>


Test::TestEntityLoader::~TestEntityLoader(void){
    delete pTexture;
    delete pShader;
    delete pMaterial;
    delete pMesh;
}

void Test::TestEntityLoader::loadEntities(void){
    srand(time(NULL));

    Test::StupidRenderer* pRenderer =
        DEVICE.getRenderThread().addRenderer(
            make_unique<Test::StupidRenderer>());
    DEVICE.getUniverse().addChild(
        make_unique<Test::Camera>(pRenderer));

    // resources (non-RAII)
    pTexture = new Texture(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_WRAP_BORDER, GL_WRAP_BORDER, 4);
    pTexture->loadFromFile("res/textures/edwerd.png");

    pShader = new Shader();
    pShader->addShaderObject(GL_VERTEX_SHADER, "shaders/VS_texture_normal.glsl");
    pShader->addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_texture_normal.glsl");
    pShader->link();

    pMaterial = new Material(GL_TEXTURE0, pTexture, pShader, "MVP");

    pMesh = new Mesh(pMaterial);
    makeUVSphere(pMesh->getVBO(), pMesh->getIBO(), pMesh->getVAO(), pMesh->getNIndices(), 32, 16);

    for(int i = 0; i < 100; i++){
        DEVICE.getUniverse().addChild(
            make_unique<Test::SingleMeshEntity>(
                pRenderer,
                pMesh,
                glm::translate(glm::mat4(1.0f),
                               glm::vec3(50.0f-(rand()%10000)/100.0f,
                                         50.0f-(rand()%10000)/100.0f,
                                         50.0f-(rand()%10000)/100.0f))));
    }
}
