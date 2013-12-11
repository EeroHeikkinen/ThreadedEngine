#ifndef MATERIAL_HH
#define MATERIAL_HH


#include <GL/GLEW.h>
#include <mutex>
#include <unordered_map>
#include <string>


class Texture;
class Shader;


class Material {
public:
    Material(void) {}
    Material(GLenum texid, Texture* pTexture_, Shader* pShader_);
    Material(std::unordered_map<GLenum, Texture*>& pTextures_, Shader* pShader_);

    void use(void) const;

    Shader* getShaderPtr(void) const;

private:
    std::unordered_map<GLenum, Texture*> pTextures;
    Shader* pShader;

    std::mutex mutex;
};


#endif // MATERIAL_HH
