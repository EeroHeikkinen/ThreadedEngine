#include "mesh.hh"
#include "material.hh"
#include "shader.hh"
#include <iostream>


Mesh::Mesh(void) {
    std::cout << "Making mesh!" << std::endl;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    glGenVertexArrays(1, &VAO);
}

Mesh::~Mesh(void) {
    std::cout << "Deleting mesh" << std::endl;
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
