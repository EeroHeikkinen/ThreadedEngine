#include "resource_loader.hh"
#include "device.hh"
#include "make_unique.hh"


void ResourceLoader::loadResource(ResourceType resType, const std::string& id) {
    DEVICE.getResourceThread().pushResourceLoadCall(
        std::make_pair(
            std::make_pair(this, &ResourceLoader::load),
            std::make_pair(resType, id)
        )
    );
}

Texture* StandardResourceLoader::getTexturePtr(const std::string& id) const {
    if (id != "") {
        auto it = textures.find(id);
        if (it != textures.end())
            return it->second.get();
    }
    return nullptr;
}

ShaderObject* StandardResourceLoader::getShaderObjectPtr(const std::string& id) const {
    if (id != "") {
        auto it = shaderObjects.find(id);
        if (it != shaderObjects.end())
            return it->second.get();
    }
    return nullptr;
}


Shader* StandardResourceLoader::getShaderPtr(const std::string& id) const {
    if (id != "") {
        auto it = shaders.find(id);
        if (it != shaders.end())
            return it->second.get();
    }
    return nullptr;
}

Material* StandardResourceLoader::getMaterialPtr(const std::string& id) const {
    if (id != "") {
        auto it = materials.find(id);
        if (it != materials.end())
            return it->second.get();
    }
    return nullptr;
}

Mesh* StandardResourceLoader::getMeshPtr(const std::string& id) const {
    if (id != "") {
        auto it = meshes.find(id);
        if (it != meshes.end())
            return it->second.get();
    }
    return nullptr;
}

bool StandardResourceLoader::setTextureInfo(const std::string& id, const std::string& fileName,
                                            GLenum minFilter_, GLenum magFilter_,
                                            GLenum sWrap_, GLenum tWrap_, GLuint AFLevel_) {
    std::lock_guard<std::mutex> lock(mutex);
    if (id == "" || fileName == "")
        return false;

    Texture::Info info;
    info.minFilter = minFilter_;
    info.magFilter = magFilter_;
    info.sWrap = sWrap_;
    info.tWrap = tWrap_;
    info.AFLevel = AFLevel_;

    textureInfos[id] = std::make_pair(fileName, info);
    return true;
}

bool StandardResourceLoader::setShaderObjectInfo(const std::string& id,
                                                 const std::string& fileName,
                                                 GLenum type) {
    std::lock_guard<std::mutex> lock(mutex);
    if (id == "" || fileName == "")
        return false;

    shaderObjectInfos[id] = std::make_pair(fileName, type);
    return true;
}

bool StandardResourceLoader::setShaderProgramInfo(const std::string& id,
                                                  const std::vector<std::string>& vShaderObjectIds) {
    std::lock_guard<std::mutex> lock(mutex);
    if (id == "")
        return false;

    shaderProgramInfos[id] = vShaderObjectIds;
    return true;
}

void StandardResourceLoader::load(ResourceType resType, std::string id) {
    std::lock_guard<std::mutex> lock(mutex);

    switch (resType) {
    case TEXTURE_IMG:
        {
            std::pair<std::string, Texture::Info> info = textureInfos.find(id)->second;
            std::unique_ptr<Texture> pTexture
                = make_unique<Texture>(info.second.minFilter, info.second.magFilter,
                                       info.second.sWrap, info.second.tWrap, info.second.AFLevel);

            pTexture->loadFromFile(info.first);

            textures[id] = std::move(pTexture);
        }
    break;

    case SHADER_OBJECT:
        {
            std::pair<std::string, GLenum> info = shaderObjectInfos.find(id)->second;
            std::unique_ptr<ShaderObject> pShaderObject
                = make_unique<ShaderObject>(info.second, info.first);

            shaderObjects[id] = std::move(pShaderObject);
        }
    break;

    case SHADER:
        {
            std::vector<std::string> vObjIds = shaderProgramInfos.find(id)->second;
            std::unique_ptr<Shader> pShader = make_unique<Shader>();

            for (auto& id : vObjIds) {
                ShaderObject* pShaderObject = getShaderObjectPtr(id);
                if (pShaderObject != nullptr)
                    pShader->addShaderObject(pShaderObject);
            }

            pShader->link();

            shaders[id] = std::move(pShader);
        }
    break;

    case MATERIAL:
        {
            std::pair<std::unordered_map<GLenum, std::string>, std::string> info = materialInfos.find(id)->second;
            std::unordered_map<GLenum, Texture*> pTextures;
            for (auto& texInfo : info.first) {
                texInfo.first
            }

            std::unique_ptr<Material> pMaterial = make_unique<Material>(info.first, );

            for () {

            }
        }
    break;

    case INVALID_TYPE:
        return;
    break;

    default:
        return;
    break;
    }

    return;
}

/*void StandardResourceLoader::addTexture(const std::string& id, Texture* texture) {
    std::lock_guard<std::mutex> lock(mutex);
    textures.emplace(id, texture);
}

void StandardResourceLoader::addShader(const std::string& id, Shader* shader) {
    std::lock_guard<std::mutex> lock(mutex);
    shaders.emplace(id, shader);
}

void StandardResourceLoader::addMaterial(const std::string& id, Material* material) {
    std::lock_guard<std::mutex> lock(mutex);
    materials.emplace(id, material);
}

void StandardResourceLoader::addMesh(const std::string& id, Mesh* mesh) {
    std::lock_guard<std::mutex> lock(mutex);
    meshes.emplace(id, mesh);
}*/
