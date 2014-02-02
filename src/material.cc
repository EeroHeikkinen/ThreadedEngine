#include "material.hh"
#include "texture.hh"
#include "shader.hh"


MaterialInfo::MaterialInfo(Shader* pShader_){
    pShader = pShader_;
}

void MaterialInfo::addTexture(GLenum texType, Texture* pTexture){
    pTextures.emplace(texType, pTexture);
}

// Material

Material* Material::getPtr(void) {
    return this;
}

bool Material::load(MaterialInfo& info){
    pShader = info.pShader;
    pTextures = info.pTextures;
}

void Material::use(void) const{
    glUseProgram(pShader->getID());

    for (auto it = pTextures.begin(); it != pTextures.end(); it++){
        // the texture unit (GLenum)
        glActiveTexture(it->first);
        // the actual texture id
        glBindTexture(GL_TEXTURE_2D, it->second->getTexture());
    }
}

Shader* Material::getShaderPtr(void) const{
    return pShader;
}
