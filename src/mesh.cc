#include "mesh.hh"
#include "material.hh"
#include "shader.hh"
#include <iostream>


Mesh::Mesh(void) {
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    glGenVertexArrays(1, &VAO);
}

Mesh::~Mesh(void) {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

GLuint& Mesh::getVBO(void) {
    return VBO;
}

GLuint& Mesh::getIBO(void) {
    return IBO;
}

GLuint& Mesh::getVAO(void) {
    return VAO;
}

unsigned int& Mesh::getNIndices(void) {
    return nIndices;
}
