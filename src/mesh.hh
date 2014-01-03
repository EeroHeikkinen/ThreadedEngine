#ifndef MESH_HH
#define MESH_HH

#include "resource.hh"

#include <GL/GLEW.h>
#include <glm/glm.hpp>
#include <mutex>

class Material;


class MeshInfo {
public:
    enum Type {
        TYPE_BOX,
        TYPE_UVSHPERE
    };

    Type type;
    float boxSizeX, boxSizeY, boxSizeZ;
    size_t sphereNumSegments, sphereNumRings;

    MeshInfo(Type type_);
    MeshInfo(Type type_, float boxSizeX_, float boxSizeY_, float boxSizeZ_);
    MeshInfo(Type type_, size_t sphereNumSegments_, size_t sphereNumRings_);
};


class Mesh {
public:
    Mesh(void);
    ~Mesh(void);

    // resource member functions
    virtual Mesh* getPtr(void) const;
    virtual bool load(MeshInfo& info);

    GLuint& getVBO(void);               //TEMP?
    GLuint& getIBO(void);               //TEMP?
    GLuint& getVAO(void);               //TEMP?
    unsigned int& getNIndices(void);    //TEMP?

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

private:
    GLuint VBO, IBO, VAO;
    unsigned int nIndices;
    Material* pMaterial;

    std::mutex mutex;
};


#endif // MESH_HH
