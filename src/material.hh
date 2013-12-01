#ifndef MATERIAL_HH
#define MATERIAL_HH


#include <GL/GLEW.h>
#include <mutex>
#include <map>
#include <string>


class Texture;
class Shader;


class Material {
public:
    Material(void) {}
    Material(GLenum texid, Texture* pTexture_, Shader* pShader_, const std::string& MVPstr);
    Material(std::map<GLenum, Texture*>& pTextures_, Shader* pShader_, const std::string& MVPstr);

    void use(void) const;

    GLint getMVPLocation(void) const;

private:
    std::map<GLenum, Texture*> pTextures;
    Shader* pShader;
    GLint MVPLoc;

    std::mutex mutex;
};


#endif // MATERIAL_HH
