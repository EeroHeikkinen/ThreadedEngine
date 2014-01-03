#ifndef TEXTURE_HH
#define TEXTURE_HH

#include "resource.hh"

#include <string>
#include <GL/GLEW.h>

#define FOURCC_DXT1 0x31545844 // "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // "DXT5" in ASCII


class TextureInfo : public ResourceInfo {
public:
    std::string fileName;
    GLenum
        minFilter, magFilter,   // filters for minification and magnification
        sWrap, tWrap,           // wrapping
        AFLevel;                // anisotropic filtering

    TextureInfo(const std::string fileName_,
                GLenum minFilter_, GLenum magFilter_,
                GLenum sWrap_, GLenum tWrap_,
                GLenum AFLevel_);
};


class Texture : public Resource {
public:
    Texture(void);
    virtual ~Texture(void);

    virtual Texture* getPtr(void) const;
    virtual bool load(TextureInfo& info);

    GLuint getTexture(void) const;

private:
    GLuint texture;
};


#endif // TEXTURE_HH
