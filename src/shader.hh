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


class ShaderObjectInfo : public ResourceInfo {
public:
    GLenum type;
    std::string fileName;

    ShaderObjectInfo(GLenum type_, const std::string& fileName_);
};


class ShaderObject : public Resource {
public:
    ShaderObject(void);
    ~ShaderObject(void);

    // resource member functions
    virtual ShaderObject* getPtr(void) const;
    virtual bool load(ShaderObjectInfo& info); //might throw an exception

    GLuint getID(void) const;
    std::string getShaderString(void) const;

    ShaderObject(const ShaderObject&) = delete;
    ShaderObject& operator=(const ShaderObject&) = delete;

private:
    const GLuint objectID;
    std::string strShader;
};


class ShaderInfo : public ResourceInfo {
public:
    std::vector<ShaderObject*> vpShaderObjects;

    ShaderInfo(void) {}
    ShaderInfo(ShaderObject* pShaderObj1, ShaderObject* pShaderObj2);
    ShaderInfo(std::vector<ShaderObject*>& vpShaderObjects_);

    void addShaderObject(ShaderObject* pShaderObj);
};


class Shader : public Resource {
public:
    Shader(void);
    ~Shader(void);

    // resource member functions
    virtual Shader* getPtr(void) const;
    virtual void load(void) const;

    void use(void) const;
    GLuint getID(void) const;

    Shader(const Shader&) = delete; //Ro3
    Shader& operator=(const Shader&) = delete; //Ro3

private:
    const GLuint programID;
};


#endif // SHADER_HH
