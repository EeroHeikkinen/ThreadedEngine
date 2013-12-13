#ifndef RESOURCE_LOADER_HH
#define RESOURCE_LOADER_HH

#include "resources.hh"

#include <string>
#include <unordered_map>
#include <mutex>
#include <memory>


class ResourceLoader{
public:
    ResourceLoader(void) {}
    virtual ~ResourceLoader(void) {}

    virtual void load(ResourceType resType, std::string id = "") = 0;

    ResourceLoader(const ResourceLoader&) = delete;
    ResourceLoader& operator=(const ResourceLoader&) = delete;

protected:
    std::mutex mutex;
};


class StandardResourceLoader : public ResourceLoader {
public:
    StandardResourceLoader(void) {}
    virtual ~StandardResourceLoader(void) {}

    Texture* getTexturePtr(const std::string& id = "") const;
    ShaderObject* getShaderObjectPtr(const std::string& id = "") const;
    Shader* getShaderPtr(const std::string& id = "") const;
    Material* getMaterialPtr(const std::string& id = "") const;
    Mesh* getMeshPtr(const std::string& id = "") const;

    bool setTextureInfo(const std::string& id = "", const std::string& fileName = "",
                        Texture::Type type_ = Texture::TYPE_INVALID,
                        GLenum minFilter_ = GL_LINEAR_MIPMAP_LINEAR, GLenum magFilter_ = GL_LINEAR,
                        GLenum sWrap_ = GL_WRAP_BORDER, GLenum tWrap_ = GL_WRAP_BORDER,
                        GLuint AFLevel_ = 0);

    bool setShaderObjectInfo(const std::string& id = "", const std::string& fileName = "",
                             GLenum type = GL_VERTEX_SHADER);

    bool setShaderProgramInfo(const std::string& id = "",
                              const std::vector<std::string>& vShaderObjectIds = std::vector<std::string>());

    bool setMaterialInfo(const std::string& id = "",
                         const std::unordered_map<GLenum, std::string>& textureIds = std::unordered_map<GLenum, std::string>(),
                         const std::string& shaderId = "");

    //bool setMeshInfo(const std::string& id = "", const std::string& materialId = "");

    virtual void load(ResourceType resType, std::string id = "");

    StandardResourceLoader(const StandardResourceLoader&) = delete;
    StandardResourceLoader& operator=(const StandardResourceLoader&) = delete;

private:
    std::recursive_mutex mutex;

    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
    std::unordered_map<std::string, std::unique_ptr<ShaderObject>> shaderObjects;
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<Material>> materials;
    std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes;

    std::unordered_map<std::string, std::pair<std::string, Texture::Info>> textureInfos;
    std::unordered_map<std::string, std::pair<std::string, GLenum>> shaderObjectInfos;
    std::unordered_map<std::string, std::vector<std::string>> shaderProgramInfos;
    std::unordered_map<std::string, std::pair<std::unordered_map<GLenum, std::string>, std::string>> materialInfos;
    //std::unordered_map<std::string, std::string> meshInfos;
};


#endif //RESOURCE_LOADER_HH
