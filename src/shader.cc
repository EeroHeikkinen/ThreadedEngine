#include "shader.hh"

#include <fstream>
#include <sstream>
#include <iostream>//temp


//ShaderObject

ShaderObject::ShaderObject(GLenum type_, const std::string& fileName) :
    type(type_),
    objectID(glCreateShader(type_))
    {
        load(fileName);
        compile();
    }

ShaderObject::~ShaderObject(void){
    glDeleteShader(objectID);
}

GLuint ShaderObject::getID(void) const{
    return objectID;
}

void ShaderObject::load(const std::string& fileName){
    std::ifstream file(fileName);
    std::string line;
    std::stringstream ssShader;

    if (file.is_open()){
        while (file.good()){
            getline(file, line);
            ssShader << line << std::endl;
        }

        file.close();
        strShader = ssShader.str();
    }
    else{
        /*
        TODO
        exception (file can't be opened)
        */
    }
}

void ShaderObject::compile(void) const{
    //specifying the source string
    const char* srcStr = strShader.c_str();
    glShaderSource(objectID, 1, &srcStr, NULL);

    //compiling
    glCompileShader(objectID);

    //compilation error checking
    GLint compiled = GL_FALSE;
    glGetShaderiv(objectID, GL_COMPILE_STATUS, &compiled);

    if (!compiled){
        GLint infoLogSize;
        glGetShaderiv(objectID, GL_INFO_LOG_LENGTH, &infoLogSize);

        char* infoLog = new char[infoLogSize];
        glGetShaderInfoLog(objectID, infoLogSize, &infoLogSize, infoLog);

        /*
        TODO
        exception (shader object didn't compile[include infoLog too])
        */

        delete[] infoLog;
    }
}


//Shader

Shader::Shader(void) :
    programID(glCreateProgram())
    {}

Shader::~Shader(void){
    glDeleteProgram(programID);
}

void Shader::addShaderObject(ShaderObject* pSO){
    vpSOs.push_back(pSO);
}

void Shader::addShaderObjects(const std::vector<ShaderObject*>& vObjs){
    for (auto& pShaderObject : vObjs) {
        vpSOs.push_back(pShaderObject);
    }
}

void Shader::link(void) const{
    //attach all shader objects to the program
    for (auto shaderObject : vpSOs)
        glAttachShader(programID, shaderObject->getID());

    //linking
    glLinkProgram(programID);

    //link error checking
    GLint linked = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);

    if (!linked){
        //get infoLog
        GLint infoLogSize;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &linked);

        char* infoLog = new char[infoLogSize];
        glGetProgramInfoLog(programID, infoLogSize, &infoLogSize, infoLog);

        /*
        TODO
        exception (shader program didn't link[include infoLog too])
        */

        delete[] infoLog;
    }
}

void Shader::use(void) const{
    glUseProgram(programID);
}

GLuint Shader::getID(void) const{
    return programID;
}
