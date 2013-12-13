/**
    Shader class is for handling shader programs.
    ShaderObject handles individual shader objects required to link a shader program.

    @author LehdaRi
    @date   26.10.2013
**/


#ifndef SHADER_HH
#define SHADER_HH

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>


class ShaderObject{
public:
    explicit ShaderObject(GLenum, const std::string&); //might throw an exception
    ~ShaderObject(void);

    GLuint getID(void) const;

    ShaderObject(const ShaderObject&) = delete;
    ShaderObject& operator=(const ShaderObject&) = delete;
private:
    const GLenum type;
    const GLuint objectID;

    std::string strShader;

    void load(const std::string&); //might throw an exception
    void compile(void) const; //might throw an exception
};


class Shader{
public:
    Shader(void);
    ~Shader(void);

    void addShaderObject(ShaderObject*);
    void addShaderObject(GLenum, const std::string&);
    void addShaderObjects(const std::map<GLenum, const std::string>&);
    void addShaderObjects(const std::vector<ShaderObject*>&);

    void link(void) const;
    void use(void) const;
    GLuint getID(void) const;

    Shader(const Shader&) = delete; //Ro3
    Shader& operator=(const Shader&) = delete; //Ro3
private:
    const GLuint programID;

    std::vector<ShaderObject*> vpSOs;
};


#endif // SHADER_HH
