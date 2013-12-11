#ifndef RESOURCES_HH
#define RESOURCES_HH

#include "texture.hh"
#include "shader.hh"
#include "material.hh"
#include "mesh.hh"


enum ResourceType {
    INVALID_TYPE,

    TEXTURE,
    SHADER_OBJECT,
    SHADER,
    MATERIAL,
    MESH
};


#endif // RESOURCES_HH
