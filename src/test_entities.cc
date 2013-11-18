#include "test_entities.hh"
#include "test_models.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>//TEMP

#define PI 3.14159265359


// Camera

Test::Camera::Camera(void) :
    angle(0.0f),
    pos(7.0f*sin(angle), 2.0f, 5.0f*cos(angle)),
    view(glm::lookAt(pos,                           // camera position
                     glm::vec3(0.0f, 0.0f, 0.0f),   // spot to look at
                     glm::vec3(0.0f, 1.0f, 0.0f))), // up vector
    projection(glm::perspective(60.0f,              // FOV
                                4.0f / 3.0f,        // aspect ratio
                                0.1f,               // near clipping plane
                                100.0f))            // far clipping plane
    {}

void Test::Camera::logic(void){
    angle += 0.01;
    if (angle > 2*PI) angle -= 2*PI;
    pos = glm::vec3(7.0f*sin(angle), 2.0f, 5.0f*cos(angle));
    view = glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

const glm::mat4& Test::Camera::getViewMatrix(void) const{
    return view;
}

const glm::mat4& Test::Camera::getProjectionMatrix(void) const{
    return projection;
}

//BallWatchingCamera

Test::WatcherCamera::WatcherCamera(Test::Sphere* pSphere) :
    pSphere(pSphere),
    pBox(nullptr)
    {std::cout << "Sphere" << pBox << std::endl;}

Test::WatcherCamera::WatcherCamera(Test::Box* pBox) :
    pSphere(nullptr),
    pBox(pBox)
    {std::cout << "Box" << pSphere << std::endl;}

void Test::WatcherCamera::logic(void){
    glm::vec3 target;
    if(pSphere)
        target = pSphere->getPosition();
    else if(pBox)
        target = pBox->getPosition();
    else
        target = glm::vec3(0.0f);
    //angle += 0.01;
    if (angle > 2*PI) angle -= 2*PI;
    pos = glm::vec3(5.0f*sin(angle), 2.0f, 5.0f*cos(angle));
    view = glm::lookAt(pos, target, glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

// Sphere

Test::Sphere::Sphere(btCollisionShape* collisionMesh_, PhysicsNode* parent_, glm::vec3 initialPos_, float mass_) :
    PhysicsComponent(collisionMesh_, parent_, initialPos_, model, mass_),
    model(glm::mat4(1.0f))
    {
        // Model
        Test::makeUVSphere(VBO, IBO, VAO, numIndices, 32, 16);

        // Shader
        shader.addShaderObject(GL_VERTEX_SHADER, "shaders/VS_texture_normal.glsl");
        shader.addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_texture_normal.glsl");
        shader.link();
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

Test::Box::Box(float xSize_, float ySize_, float zSize_,
               btCollisionShape* collisionMesh_, PhysicsNode* parent_,
               glm::vec3 initialPos_, float mass_) :
    PhysicsComponent(collisionMesh_, parent_, initialPos_, model, mass_),
    numIndices(36),
    model(glm::translate(glm::mat4(1.0f), initialPos_))
    {
        // Model
        Test::makeBox(VBO, IBO, VAO, xSize_, ySize_, zSize_);

        // Shader
        shader.addShaderObject(GL_VERTEX_SHADER, "shaders/VS_color.glsl");
        shader.addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_color.glsl");
        shader.link();
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
