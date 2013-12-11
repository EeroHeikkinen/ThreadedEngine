#include "texture.hh"
#include "device.hh"

#include <SFML/Graphics.hpp>
#include <iostream> //temp


Texture::Texture(Type type_,
                 GLenum minFilter_, GLenum magFilter_,
                 GLenum sWrap_, GLenum tWrap_,
                 GLuint AFLevel_)
    {
        info.type = type_;
        info.minFilter = minFilter_;
        info.magFilter = magFilter_;
        info.sWrap = sWrap_;
        info.tWrap = tWrap_;
        info.AFLevel = AFLevel_;

        glGenTextures(1, &texture);
    }

GLuint Texture::getTexture(void) {
    return texture;
}

void Texture::loadFromFile(const std::string& fileName) {
    sf::Image img;
    img.loadFromFile(fileName);

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
}
