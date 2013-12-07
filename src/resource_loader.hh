#ifndef RESOURCE_LOADER_HH
#define RESOURCE_LOADER_HH

#include "resources.hh"

#include <string>
#include <map>
#include <mutex>


class ResourceLoader {
public:
    ResourceLoader(void) {}
    virtual ~ResourceLoader(void) {}

    // called by user
    void loadResource(ResourceType resType, const std::string& id = "");

    ResourceLoader(const ResourceLoader&) = delete;
    ResourceLoader& operator=(const ResourceLoader&) = delete;

protected:
    // callback function passed to ResourceThread
    virtual void load(ResourceType resType, std::string id = "") = 0;
};


class StandardResourceLoader : public ResourceLoader {
public:
    StandardResourceLoader(void) {}
    virtual ~StandardResourceLoader(void);

    Texture* getTexturePtr(const std::string& id = "") const;
    Shader* getShaderPtr(const std::string& id = "") const;
    Material* getMaterialPtr(const std::string& id = "") const;
    Mesh* getMeshPtr(const std::string& id = "") const;

    bool setTextureInfo(const std::string& id = "", const std::string& fileName = "",
                        GLenum minFilter_ = GL_LINEAR_MIPMAP_LINEAR, GLenum magFilter_ = GL_LINEAR,
                        GLenum sWrap_ = GL_WRAP_BORDER, GLenum tWrap_ = GL_WRAP_BORDER,
                        GLuint AFLevel_ = 0);

    StandardResourceLoader(const StandardResourceLoader&) = delete;
    StandardResourceLoader& operator=(const StandardResourceLoader&) = delete;

protected:
    virtual void load(ResourceType resType, std::string id = "");

    /* probably useless
    void addTexture(const std::string& id, Texture* texture);
    void addShader(const std::string& id, Shader* shader);
    void addMaterial(const std::string& id, Material* material);
    void addMesh(const std::string& id, Mesh* mesh);*/

private:
    std::mutex mutex;

    std::map<const std::string, Texture*> textures;
    std::map<const std::string, Shader*> shaders;
    std::map<const std::string, Material*> materials;
    std::map<const std::string, Mesh*> meshes;

    std::map<const std::string, std::pair<std::string, Texture::Info>> textureInfos;
};

/*
dis too ambitious
template<typename T>
class GenericResourceLoader : public ResourceLoader {
public:
    virtual ~GenericResourceLoader(void){
        for (auto i : resources)
            delete i.second;
    }

    T* getPtr(const std::string& id = "", const std::string& fileName = "") {
        if (id != "") {
            auto it = resources.find(id);
            if (it != resources.end())
                return it->second;
        }
        return nullptr;
    }

protected:
    virtual void load(ResourceType resType, const std::string& id = "") {

    }

private:
    std::mutex mutex;
    std::map<const std::string, T*> resources;
};*/


#endif // RESOURCE_LOADER_HH
