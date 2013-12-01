#ifndef MESH_HH
#define MESH_HH


#include <GL/GLEW.h>
#include <glm/glm.hpp>
#include <mutex>


class Material;


class Mesh {
public:
    Mesh(Material* pMaterial_);
    Mesh(const Mesh&) = delete;
    ~Mesh(void);

    void render(const glm::mat4& view, const glm::mat4& projection, const glm::mat4& model) const;

    GLuint& getVBO(void);               //TEMP?
    GLuint& getIBO(void);               //TEMP?
    GLuint& getVAO(void);               //TEMP?
    unsigned int& getNIndices(void);    //TEMP?

    Mesh& operator=(const Mesh&) = delete;

private:
    GLuint VBO, IBO, VAO;
    unsigned int nIndices;
    Material* pMaterial;

    std::mutex mutex;
};


#endif // MESH_HH
