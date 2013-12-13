#include "test_entities.hh"
#include "test_models.hh"
#include "texture.hh"
#include "shader.hh"
#include "material.hh"
#include "mesh.hh"
#include "device.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265359

class StandardResourceLoader;


// Camera
Test::Camera::Camera(Test::StupidRenderer* pStupidRenderer) :
    angle(0.0f),
    pos(75.0f*sin(angle), 20.0f, 75.0f*cos(angle)),
    view(glm::lookAt(pos,                           // camera position
                     glm::vec3(0.0f, 0.0f, 0.0f),   // spot to look at
                     glm::vec3(0.0f, 1.0f, 0.0f))), // up vector
    proj(glm::perspective(60.0f,              // FOV
                          4.0f / 3.0f,        // aspect ratio
                          0.1f,               // near clipping plane
                          300.0f))            // far clipping plane
    {
        addComponent(makeLogicComponent([this](){this->logic();}));
        addComponent(make_unique<StupidCameraComponent>(pStupidRenderer,
                                                        view,
                                                        proj));

        registerComponents();
    }
Test::Camera::~Camera(void){
    unregisterComponents();
}
void Test::Camera::logic(void){
    angle += 0.0035;
    if (angle > 2*PI) angle -= 2*PI;
    pos = glm::vec3(75.0f*sin(angle), 20.0f, 75.0f*cos(angle));
    view = glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    proj = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 300.0f);

}

//SingleMeshEntity
Test::SingleMeshEntity::SingleMeshEntity(Test::StupidRenderer* pStupidRenderer,
                     Mesh* pMesh,
                     Material* pMaterial,
                     glm::mat4 _model) :
    pMesh(pMesh),
    pMaterial(pMaterial),
    model(std::move(_model))
    {
        auto rfunc = [this](const glm::mat4& view, const glm::mat4& proj){
            this->render(view, proj);
        };
        addComponent(makeStupidRenderComponent(pStupidRenderer, rfunc));

        registerComponents();
    }
Test::SingleMeshEntity::~SingleMeshEntity(void){
    unregisterComponents();
}
void Test::SingleMeshEntity::render(const glm::mat4& view, const glm::mat4& proj){
    glm::mat4 MVP = proj * view * model;

    glBindVertexArray(pMesh->getVAO());

        pMaterial->use();
        GLint MVPloc = glGetUniformLocation(pMaterial->getShaderPtr()->getID(), "MVP");
        glUniformMatrix4fv(MVPloc, 1, GL_FALSE, &MVP[0][0]);

        glDrawElements(GL_TRIANGLES, pMesh->getNIndices(), GL_UNSIGNED_SHORT, (GLvoid*)0);

    glBindVertexArray(0);
}

//Edwerd
Test::Edwerd::Edwerd(Test::StupidRenderer* pStupidRenderer, glm::mat4 _model) :
    SingleMeshEntity(
        pStupidRenderer,
        dynamic_cast<StandardResourceLoader*>
            (DEVICE.getResourceThread().getResourceLoaderPtr(MESH))
                ->getMeshPtr("sphere"),
        dynamic_cast<StandardResourceLoader*>
            (DEVICE.getResourceThread().getResourceLoaderPtr(MATERIAL))
                ->getMaterialPtr("material_edwerd"),
        std::move(_model))
    {}

//Sphere
Test::Sphere::Sphere(Test::StupidRenderer* pStupidRenderer,
                     float radius,
                     Material* pMaterial,
                     glm::vec3 initialPos,
                     glm::vec3 initialVel,
                     float mass,
                     float restitution) :
    SingleMeshEntity(
        pStupidRenderer,
        dynamic_cast<StandardResourceLoader*>
            (DEVICE.getResourceThread().getResourceLoaderPtr(MESH))
                ->getMeshPtr("sphere"),
        pMaterial,
        glm::translate(glm::mat4(1.0f), initialPos) *
            glm::scale(glm::mat4(1.0f), glm::vec3(radius))),
    scale(glm::scale(glm::mat4(1.0f), glm::vec3(radius)))
    {
        addComponent(make_unique<PhysicsComponent>(
                        make_unique<btSphereShape>(radius),
                        DEVICE.getPhysicsThread().getPhysicsTree().getRoot(),
                        std::move(initialPos),
                        std::move(initialVel),
                        model,
                        scale,
                        mass,
                        restitution));

        registerComponents();
    }
Test::Sphere::~Sphere(void){
    unregisterComponents();
}

//Box
Test::Box::Box(Test::StupidRenderer* pStupidRenderer,
               float xHalfSize, float yHalfSize, float zHalfSize,
               Material* pMaterial,
               glm::vec3 initialPos,
               glm::vec3 initialVel,
               float mass,
               float restitution) :
    SingleMeshEntity(
        pStupidRenderer,
        dynamic_cast<StandardResourceLoader*>
            (DEVICE.getResourceThread().getResourceLoaderPtr(MESH))
                ->getMeshPtr("box"),
        pMaterial,
        glm::translate(glm::mat4(1.0f), initialPos) *
            glm::scale(glm::mat4(1.0f), glm::vec3(xHalfSize,yHalfSize,zHalfSize))),
    scale(glm::scale(glm::mat4(1.0f), glm::vec3(xHalfSize,yHalfSize,zHalfSize)))
    {
        addComponent(make_unique<PhysicsComponent>(
                        make_unique<btBoxShape>(btVector3(xHalfSize,yHalfSize,zHalfSize)),
                        DEVICE.getPhysicsThread().getPhysicsTree().getRoot(),
                        std::move(initialPos),
                        std::move(initialVel),
                        model,
                        scale,
                        mass,
                        restitution));

        registerComponents();
    }
Test::Box::~Box(void){
    unregisterComponents();
}


//EdwerdCollection
Test::EdwerdCollection::EdwerdCollection(Test::StupidRenderer* pRenderer){
    srand(time(NULL));

    for(int i = 0; i < 100; ++i){
        this->addChild(
            make_unique<Test::Edwerd>(
                pRenderer,
                glm::translate(glm::mat4(1.0f),
                               glm::vec3(50.0f-(rand()%10000)/100.0f,
                                         50.0f-(rand()%10000)/100.0f,
                                         50.0f-(rand()%10000)/100.0f))));
    }
}
