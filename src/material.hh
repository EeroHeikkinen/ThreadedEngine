#ifndef MATERIAL_HH
#define MATERIAL_HH

#include "resource.hh"

#include <GL/GLEW.h>
#include <unordered_map>
#include <string>
#include <mutex>

class Texture;
class Shader;


class MaterialInfo : public ResourceInfo {
public:
    std::unordered_map<GLenum, Texture*> pTextures;
    Shader* pShader;

    MaterialInfo(void) {};
    MaterialInfo(Shader* pShader_);

    void addTexture(GLenum texType, Texture* pTexture);
};

class Material : public Resource {
public:
    Material(void) {}
    ~Material(void) {}

    // resource member functions
    virtual Material* getPtr(void);
    virtual bool load(MaterialInfo& info);

    void use(void) const;
    Shader* getShaderPtr(void) const;

private:
    std::unordered_map<GLenum, Texture*> pTextures;
    Shader* pShader;
};


#endif // MATERIAL_HH
