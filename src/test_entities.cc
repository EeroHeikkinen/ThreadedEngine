#include "test_entities.hh"

#include <iostream>//TEMP

#define PI 3.14159265359


test::TriangleRender::TriangleRender(void) {
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

void test::TriangleRender::render(void) {
    glBindVertexArray(VAO);
    shader.use();

    GLint translationLoc = glGetUniformLocation(shader.getID(), "translation");
    glm::vec3 pos = dynamic_cast<TriangleLogic*>(this)->getPosition();

    glProgramUniform3fv(shader.getID(), translationLoc, 1, &pos[0]);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (GLvoid*)0);
    glBindVertexArray(0);
}


test::TriangleLogic::TriangleLogic(void) :
    alpha(0.0f),
    pos(0.8f*cosf(alpha), 0.8f*sinf(alpha), 0.0f) { }

void test::TriangleLogic::logic(void) {
    alpha += 0.01;
    if (alpha > 2*PI)
        alpha -= 2*PI;
    pos = glm::vec3(0.8f*cosf(alpha), 0.8f*sinf(alpha), 0.0f);
}

glm::vec3 test::TriangleLogic::getPosition(void) {
    return pos;
}
