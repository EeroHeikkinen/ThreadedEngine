#include "test_entities.hh"
#include "test_models.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>//TEMP


#define PI 3.14159265359


// Camera

test::Camera::Camera(void) :
    angle(0.0f),
    pos(7.0f*sin(angle), 2.0f, 5.0f*cos(angle)),
    view(glm::lookAt(
                     pos,                           // camera position
                     glm::vec3(0.0f, 0.0f, 0.0f),   // spot to look at
                     glm::vec3(0.0f, 1.0f, 0.0f)    // up vector
                     )),
    projection(glm::perspective(
                                60.0f,              // FOV
                                4.0f / 3.0f,        // aspect ratio
                                0.1f,               // near clipping plane
                                100.0f              // far clipping plane
                                )) { }

void test::Camera::logic(void) {
    angle += 0.01;
    if (angle > 2*PI) angle -= 2*PI;
    pos = glm::vec3(7.0f*sin(angle), 2.0f, 5.0f*cos(angle));
    view = glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

const glm::mat4& test::Camera::getViewMatrix(void) const {
    return view;
}

const glm::mat4& test::Camera::getProjectionMatrix(void) const {
    return projection;
}


// Sphere

test::Sphere::Sphere(btCollisionShape* collisionMesh_, PhysicsNode* parent, glm::vec3 pos, float mass_) :
    PhysicsComponent(collisionMesh_, parent, pos, model, mass_), model(glm::mat4(1.0f)) {
    // Model
    test::makeUVSphere(VBO, IBO, VAO, numIndices, 32, 16);

    // Shader
    shader.addShaderObject(GL_VERTEX_SHADER, "shaders/VS_texture_normal.glsl");
    shader.addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_texture_normal.glsl");
    shader.link();
}


test::Sphere::~Sphere(void) {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

void test::Sphere::render(const glm::mat4& view, const glm::mat4& projection) {

    glm::mat4 MVP = projection * view * model;

    glBindVertexArray(VAO);
    shader.use();

    GLint MVPLoc = glGetUniformLocation(shader.getID(), "MVP");

    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &MVP[0][0]);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, (GLvoid*)0);
    glBindVertexArray(0);
}


//Box

test::Box::Box(float xSize, float ySize, float zSize, glm::vec3 pos) :
    numIndices(36),
    model(glm::translate(glm::mat4(1.0f), pos)) {
    // Model
    test::makeBox(VBO, IBO, VAO, xSize, ySize, zSize);

    // Shader
    shader.addShaderObject(GL_VERTEX_SHADER, "shaders/VS_color.glsl");
    shader.addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_color.glsl");
    shader.link();
}

test::Box::~Box(void) {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

void test::Box::render(const glm::mat4& view, const glm::mat4& projection) {
    glm::mat4 MVP = projection * view * model;

    glBindVertexArray(VAO);
    shader.use();

    GLint MVPLoc = glGetUniformLocation(shader.getID(), "MVP");

    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &MVP[0][0]);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, (GLvoid*)0);
    glBindVertexArray(0);
}
