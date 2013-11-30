#include "material.hh"
#include "texture.hh"
#include "shader.hh"


Material::Material(GLenum texid, Texture* pTexture_, Shader* pShader_, const std::string& MVPstr) {
    std::lock_guard<std::mutex> lock(mutex);

    pTextures.emplace(texid, pTexture_);
    pShader = pShader_;
    MVPLoc = glGetUniformLocation(pShader->getID(), MVPstr.c_str());
    /*
    TODO
    if MVPloc < 0 an exception should be thrown.
    */
}

Material::Material(std::map<GLenum, Texture*>& pTextures_, Shader* pShader_, const std::string& MVPstr) {
    std::lock_guard<std::mutex> lock(mutex);

    pTextures.insert(pTextures_.begin(), pTextures.end());
    pShader = pShader_;
    MVPLoc = glGetUniformLocation(pShader->getID(), MVPstr.c_str());
    /*
    TODO
    same as above
    */
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

GLint Material::getMVPLocation(void) const {
    return MVPLoc;
}
