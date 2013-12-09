#include "test_entities.hh"
#include "test_models.hh"
#include "mesh.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>//TEMP

#define PI 3.14159265359


// Camera
Test::Camera::Camera(Test::StupidRenderer* pStupidRenderer) :
    angle(0.0f),
    pos(25.0f*sin(angle), 0.0f, 20.0f*cos(angle)),
    view(glm::lookAt(pos,                           // camera position
                     glm::vec3(0.0f, 0.0f, 0.0f),   // spot to look at
                     glm::vec3(0.0f, 1.0f, 0.0f))), // up vector
    proj(glm::perspective(60.0f,              // FOV
                                4.0f / 3.0f,        // aspect ratio
                                0.1f,               // near clipping plane
                                100.0f))            // far clipping plane
    {
        addComponent(makeLogicComponent([this](){this->logic();}));
        addComponent(makeStupidCameraComponent(pStupidRenderer,
                                               view,
                                               proj));
    }

void Test::Camera::logic(void){
    angle += 0.0035;
    if (angle > 2*PI) angle -= 2*PI;
    pos = glm::vec3(25.0f*sin(angle), 0.0f, 20.0f*cos(angle));
    view = glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    proj = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

}

// SingleMeshEntity
Test::SingleMeshEntity::SingleMeshEntity(Test::StupidRenderer* pStupidRenderer,
                                         Mesh* pMesh,
                                         glm::mat4 _model) :
    pMesh(pMesh),
    model(std::move(_model))
    {
        auto rfunc = [this](const glm::mat4& view, const glm::mat4& proj){
            this->render(view, proj);
        };
        addComponent(makeStupidRenderComponent(pStupidRenderer, rfunc));
    }

void Test::SingleMeshEntity::render(const glm::mat4& view, const glm::mat4& projection){
    pMesh->render(view, projection, model);
}

// Sphere
Test::Sphere::Sphere(Test::StupidRenderer* pStupidRenderer,
                     std::unique_ptr<btCollisionShape> pCollisionMesh,
                     PhysicsNode* pParent,
                     glm::vec3 initialPos,
                     glm::vec3 initialVel,
                     float mass,
                     float restitution) :
    model(glm::translate(glm::mat4(1.0f), initialPos))
    {
        // Model
        Test::makeUVSphere(VBO, IBO, VAO, numIndices, 32, 16);

        // Shader
        shader.addShaderObject(GL_VERTEX_SHADER, "shaders/VS_texture_normal.glsl");
        shader.addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_texture_normal.glsl");
        shader.link();

        addComponent(makePhysicsComponent(std::move(pCollisionMesh),
                                          pParent,
                                          std::move(initialPos),
                                          std::move(initialVel),
                                          model,
                                          mass,
                                          restitution));
        auto rfunc = [this](const glm::mat4& view, const glm::mat4& proj){
            this->render(view, proj);
        };
        addComponent(makeStupidRenderComponent(pStupidRenderer, rfunc));
    }

Test::Sphere::~Sphere(void){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

void Test::Sphere::render(const glm::mat4& view, const glm::mat4& projection){
    glm::mat4 MVP = projection * view * model;

    glBindVertexArray(VAO);
    shader.use();

    GLint MVPLoc = glGetUniformLocation(shader.getID(), "MVP");

    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &MVP[0][0]);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, (GLvoid*)0);
    glBindVertexArray(0);
}

glm::vec3 Test::Sphere::getPosition(void){
    return glm::vec3(model * glm::vec4(0.0f,0.0f,0.0f,1.0f));
}

//Box
Test::Box::Box(Test::StupidRenderer* pStupidRenderer,
               float xHalfSize, float yHalfSize, float zHalfSize,
               std::unique_ptr<btCollisionShape>pCollisionMesh,
               PhysicsNode* pParent,
               glm::vec3 initialPos,
               glm::vec3 initialVel,
               float mass,
               float restitution) :
    numIndices(36),
    model(glm::translate(glm::mat4(1.0f), initialPos))
    {
        // Model
        Test::makeBox(VBO, IBO, VAO, xHalfSize, yHalfSize, zHalfSize);

        // Shader
        shader.addShaderObject(GL_VERTEX_SHADER, "shaders/VS_color.glsl");
        shader.addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_color.glsl");
        shader.link();

        addComponent(makePhysicsComponent(std::move(pCollisionMesh),
                                          pParent,
                                          std::move(initialPos),
                                          std::move(initialVel),
                                          model,
                                          mass,
                                          restitution));
        auto rfunc = [this](const glm::mat4& view, const glm::mat4& proj){
            this->render(view, proj);
        };
        addComponent(makeStupidRenderComponent(pStupidRenderer, rfunc));
    }

Test::Box::~Box(void){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

void Test::Box::render(const glm::mat4& view, const glm::mat4& projection) {
    glm::mat4 MVP = projection * view * model;

    glBindVertexArray(VAO);
    shader.use();

    GLint MVPLoc = glGetUniformLocation(shader.getID(), "MVP");

    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &MVP[0][0]);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, (GLvoid*)0);
    glBindVertexArray(0);
}

glm::vec3 Test::Box::getPosition(void){
    return glm::vec3(model * glm::vec4(0.0f,0.0f,0.0f,1.0f));
}
