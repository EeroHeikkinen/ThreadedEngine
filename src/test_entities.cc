#include "test_entities.hh"
#include "test_models.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>//TEMP


#define PI 3.14159265359


//Camera

test::Camera::Camera(void) :
    pos(0.0f, 0.0f, 1.0f),
    view(glm::lookAt(
                     pos,                           // camera position
                     glm::vec3(0.0f, 0.0f, 0.0f),   // spot to look at
                     glm::vec3(0.0f, 1.0f, 0.0f)    // up vector
                     )),
    projection(glm::perspective(
                                70.0f,              // FOV
                                4.0f / 3.0f,        // aspect ratio
                                0.1f,               // near clipping plane
                                100.0f              // far clipping plane
                                )) { }

void test::Camera::logic(void) {

}

const glm::mat4& test::Camera::getViewMatrix(void) const {
    return view;
}

const glm::mat4& test::Camera::getProjectionMatrix(void) const {
    return projection;
}


//Triangle

test::Triangle::Triangle(void) :
    alpha(0.0f),
    pos(0.8f*cosf(alpha), 0.8f*sinf(alpha), 0.0f) {
    // some vertex data
    const GLuint nVertices = 3;
    const GLfloat vertices[] = {
        -0.2f, -0.2f, 0.0f,
        0.0f, 0.2f, 0.0f,
        0.2f, -0.2f, 0.0f
    };

    const GLuint nIndices = 3;
    const GLushort indices[] = {
        0, 1, 2
    };

    // generating buffers
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    glGenVertexArrays(1, &VAO);

    // filling the buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 4*3*nVertices, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2*nIndices, indices, GL_STATIC_DRAW);

    // configuring the vertex array object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    // VAO done, unbinding
    glBindVertexArray(0);

    //Shader
    shader.addShaderObject(GL_VERTEX_SHADER, "shaders/VS_test1a.glsl");
    shader.addShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_test1a.glsl");
    shader.link();
}

test::Triangle::~Triangle(void) {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

void test::Triangle::render(const glm::mat4& view, const glm::mat4& projection) {
    glm::mat4 MVP = projection * view;

    glBindVertexArray(VAO);
    shader.use();

    GLint MVPLoc = glGetUniformLocation(shader.getID(), "MVP");

    glProgramUniformMatrix4fv(shader.getID(), MVPLoc, 1, false, &MVP[0][0]);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (GLvoid*)0);
    glBindVertexArray(0);
}

void test::Triangle::logic(void) {
    alpha += 0.01;
    if (alpha > 2*PI)
        alpha -= 2*PI;
    pos = glm::vec3(0.8f*cosf(alpha), 0.8f*sinf(alpha), 0.0f);
}
