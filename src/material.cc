#include "material.hh"
#include "texture.hh"
#include "shader.hh"


Material::Material(GLenum texid, Texture* pTexture_, Shader* pShader_, const std::string& MVPstr) {
    std::lock_guard<std::mutex> lock(mutex);

    pTextures.emplace(texid, pTexture_);
    pShader = pShader_;
}

Material::Material(std::map<GLenum, Texture*>& pTextures_, Shader* pShader_, const std::string& MVPstr) {
    std::lock_guard<std::mutex> lock(mutex);

    pTextures.insert(pTextures_.begin(), pTextures.end());
    pShader = pShader_;
}

void Material::use(void) const {
    glUseProgram(pShader->getID());

    for (auto it = pTextures.begin(); it != pTextures.end(); it++) {
        // the texture unit (GLenum)
        glActiveTexture(it->first);
        // the actual texture id
        glBindTexture(GL_TEXTURE_2D, it->second->getTexture());
    }
}

Shader* Material::getShaderPtr(void) const {
    return pShader;
}
