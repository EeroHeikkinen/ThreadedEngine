#include "texture.hh"
#include "device.hh"

#include <SFML/Graphics.hpp>


TextureInfo::TextureInfo(const std::string fileName_
                         GLenum minFilter_, GLenum magFilter_,
                         GLenum sWrap_, GLenum tWrap_,
                         GLenum AFLevel_) :
    fileName(fileName_),
    minFilter(minFilter_), magFilter(magFilter_),
    sWrap(sWrap_), tWrap(tWrap_),
    AFLevel(AFLevel_)
    {}


Texture::Texture(void)
    {
        glGenTextures(1, &texture);
    }

Texture::~Texture(void){
    glDeleteTextures(1, &texture);
}

virtual Texture* getPtr(void) const{
    return getPtr;
}

virtual bool Texture::load(TextureInfo& info){
    sf::Image img;
    img.loadFromFile(info.fileName);

    // binding the texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // uploading the image to the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 img.getSize().x, img.getSize().y,
                 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 img.getPixelsPtr());

    // wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, info.sWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, info.tWrap);

    // minification/magnification filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, info.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, info.magFilter);

    // anisotropic filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, info.AFLevel);

    // mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

GLuint Texture::getTexture(void) const{
    return texture;
}
