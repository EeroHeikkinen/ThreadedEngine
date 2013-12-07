#ifndef TEXTURE_HH
#define TEXTURE_HH


#include <string>
#include <GL/GLEW.h>


#define FOURCC_DXT1 0x31545844 // "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // "DXT5" in ASCII


class Texture{
public:
    struct Info {
        GLenum
            minFilter, magFilter,   // filters for minification and magnification
            sWrap, tWrap,           // wrapping
            AFLevel;                // anisotropic filtering
    };

    Texture(GLenum minFilter_, GLenum magFilter_,
            GLenum sWrap_, GLenum tWrap_,
            GLuint AFLevel_);

    GLuint getTexture(void);

    void loadFromFile(const std::string& fileName);

private:
    GLuint texture;
    Info info;
};


#endif // TEXTURE_HH
