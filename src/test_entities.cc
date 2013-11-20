#include "test_entities.hh"
#include "test_models.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>//TEMP

#define PI 3.14159265359


// Camera

Test::Camera::Camera(void) :
    angle(0.0f),
    pos(7.0f*sin(angle), 0.2f, 6.0f*cos(angle)),
    view(glm::lookAt(pos,                           // camera position
                     glm::vec3(0.0f, 0.6f, 0.0f),   // spot to look at
                     glm::vec3(0.0f, 1.0f, 0.0f))), // up vector
    projection(glm::perspective(60.0f,              // FOV
                                4.0f / 3.0f,        // aspect ratio
                                0.1f,               // near clipping plane
                                100.0f))            // far clipping plane
    {}

void Test::Camera::logic(void){
    angle += 0.01;
    if (angle > 2*PI) angle -= 2*PI;
    pos = glm::vec3(7.0f*sin(angle), 0.2f, 6.0f*cos(angle));
    view = glm::lookAt(pos, glm::vec3(0.0f, 0.6f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

const glm::mat4& Test::Camera::getViewMatrix(void) const{
    return view;
}

const glm::mat4& Test::Camera::getProjectionMatrix(void) const{
    return projection;
}

// Sphere

Test::Sphere::Sphere(glm::mat4 model_) :
    model(model_),
    texture(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_WRAP_BORDER, GL_WRAP_BORDER, 0)
{
    // Model
    Test::makeUVSphere(VBO, IBO, VAO, numIndices, 32, 16);

    // Shader
    shader.addShaderObject(GL_VERTEX_SHADER, "shaders/VS_texture_normal.glsl");
    shader.addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_texture_normal.glsl");
    shader.link();

    // Texture
    texture.loadFromFile("res/textures/edwerd.png");
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

    // model matrix
    GLint MVPLoc = glGetUniformLocation(shader.getID(), "MVP");
    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &MVP[0][0]);

    // texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTexture());

    // draw
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, (GLvoid*)0);

    glBindVertexArray(0);
}

glm::vec3 Test::Sphere::getPosition(void){
    return glm::vec3(model * glm::vec4(0.0f,0.0f,0.0f,1.0f));
}

//Box

Test::Box::Box(float xSize_, float ySize_, float zSize_, glm::mat4 model_) :
    numIndices(36),
    model(model_)
{
    // Model
    Test::makeBox(VBO, IBO, VAO, xSize_, ySize_, zSize_);

    // Shader
    shader.addShaderObject(GL_VERTEX_SHADER, "shaders/VS_color.glsl");
    shader.addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_color.glsl");
    shader.link();
}

Test::Box::~Box(void) {
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
