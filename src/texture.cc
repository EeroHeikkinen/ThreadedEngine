#include "texture.hh"


#include <SFML/Graphics.hpp>


Texture::Texture(GLenum minFilter_, GLenum magFilter_,
                 GLenum sWrap_, GLenum tWrap_,
                 GLuint AFLevel_) :
    minFilter(minFilter_), magFilter(magFilter_),
    sWrap(sWrap_), tWrap(tWrap_), AFLevel(AFLevel_)
    {
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);

    // minification/magnification filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    // anisotropic filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, AFLevel);

    // mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
}
