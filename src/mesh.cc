#include "mesh.hh"
#include "material.hh"
#include "shader.hh"


MeshInfo::MeshInfo(Type type_) :
    type(type_)
    {}

MeshInfo::MeshInfo(Type type_,
                   float boxSizeX_,
                   float boxSizeY_,
                   float boxSizeZ_) :
    type(type_),
    boxSizeX(boxSizeX_),
    boxSizeY(boxSizeY_),
    boxSizeZ(boxSizeZ_)
    {}

MeshInfo::MeshInfo(Type type_,
                   size_t sphereNumSegments_,
                   size_t sphereNumRings_) :
    type(type_),
    sphereNumSegments(sphereNumSegments_),
    sphereNumRings(sphereNumRings_)
    {}


Mesh::Mesh(void){
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    glGenVertexArrays(1, &VAO);
}

Mesh::~Mesh(void){
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
