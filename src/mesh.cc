#include "mesh.hh"
#include "material.hh"


Mesh::Mesh(Material* pMaterial_) {
    pMaterial = pMaterial_;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    glGenVertexArrays(1, &VAO);
}

Mesh::~Mesh(void) {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::render(const glm::mat4& view, const glm::mat4& projection, const glm::mat4& model) const {
    glm::mat4 MVP = projection * view * model;

    // bind VAO
    glBindVertexArray(VAO);

    // use material
    pMaterial->use();

    // upload MVP matrix
    glUniformMatrix4fv(pMaterial->getMVPLocation(), 1, GL_FALSE, &MVP[0][0]);

    // draw
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_SHORT, (GLvoid*)0);

    // unbind VAO
    glBindVertexArray(0);

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
