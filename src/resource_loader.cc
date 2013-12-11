#include "resource_loader.hh"
#include "device.hh"
#include "make_unique.hh"
#include "test_models.hh" // TEMP


void ResourceLoader::loadResource(ResourceType resType, const std::string& resId){
    ResourceThread::ResourceLoadCall call = {this, &ResourceLoader::load, resType, resId};
    DEVICE.getResourceThread().pushResourceLoadCall(call);
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
    if (id != ""){
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
    if (id != ""){
        auto it = meshes.find(id);
        if (it != meshes.end())
            return it->second.get();
    }
    return nullptr;
}

bool StandardResourceLoader::setTextureInfo(const std::string& id, const std::string& fileName,
                                            Texture::Type type_,
                                            GLenum minFilter_, GLenum magFilter_,
                                            GLenum sWrap_, GLenum tWrap_, GLuint AFLevel_) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    if (id == "" || fileName == "")
        return false;

    Texture::Info info;
    info.type = type_;
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
    std::lock_guard<std::recursive_mutex> lock(mutex);
    if (id == "" || fileName == "")
        return false;

    shaderObjectInfos[id] = std::make_pair(fileName, type);
    return true;
}

bool StandardResourceLoader::setShaderProgramInfo(const std::string& id,
                                                  const std::vector<std::string>& vShaderObjectIds) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    if (id == "" || vShaderObjectIds.size() == 0)
        return false;

    shaderProgramInfos[id] = vShaderObjectIds;
    return true;
}

bool StandardResourceLoader::setMaterialInfo(const std::string& id,
                                             const std::unordered_map<GLenum, std::string>& textureIds,
                                             const std::string& shaderId) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    if (id == "" || textureIds.size() == 0 || shaderId == "")
        return false;

    materialInfos[id] = std::make_pair(textureIds, shaderId);
    return true;
}

bool StandardResourceLoader::setMeshInfo(const std::string& id,
                                         const std::string& materialId) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    if (id == "" || materialId == "")
        return false;

    meshInfos[id] = materialId;
    return true;
}

void StandardResourceLoader::load(ResourceType resType, std::string id) {
    std::lock_guard<std::recursive_mutex> lock(mutex);

    switch (resType) {
    case TEXTURE:
        {
            auto it = textureInfos.find(id);
            if (it == textureInfos.end()) {
                /*
                TODO
                cannot load resource; throw an exception */
            }

            std::pair<std::string, Texture::Info> info = it->second;
            std::unique_ptr<Texture> pTexture
                = make_unique<Texture>(info.second.type, info.second.minFilter, info.second.magFilter,
                                       info.second.sWrap, info.second.tWrap, info.second.AFLevel);

            switch (info.second.type) {
                case Texture::Type::IMG:
                    pTexture->loadFromFile(info.first);
                break;

                case Texture::Type::INVALID:
                    //TODO exception?
                break;

                default:
                    //TODO exception?
                break;
            }

            textures[id] = std::move(pTexture);
        }
    break;

    case SHADER_OBJECT:
        {
            auto it = shaderObjectInfos.find(id);
            if (it == shaderObjectInfos.end()) {
                /*
                TODO
                cannot load resource; throw an exception */
            }

            std::pair<std::string, GLenum> info = it->second;
            std::unique_ptr<ShaderObject> pShaderObject
                = make_unique<ShaderObject>(info.second, info.first);

            shaderObjects[id] = std::move(pShaderObject);
        }
    break;

    case SHADER:
        {
            auto it = shaderProgramInfos.find(id);
            if (it == shaderProgramInfos.end()) {
                /*
                TODO
                cannot load resource; throw an exception */
            }

            std::vector<std::string> vObjIds = it->second;
            std::unique_ptr<Shader> pShader = make_unique<Shader>();

            for (auto& objId : vObjIds) { // let's add shader objects
                ShaderObject* pShaderObject = getShaderObjectPtr(objId);
                if (pShaderObject == nullptr) { // object not loaded, load it
                    load(SHADER_OBJECT, objId);
                    pShaderObject = getShaderObjectPtr(objId);
                }

                pShader->addShaderObject(pShaderObject);
            }

            pShader->link();

            shaders[id] = std::move(pShader);
        }
    break;

    case MATERIAL:
        {
            auto it = materialInfos.find(id);
            if (it == materialInfos.end()) {
                /*
                TODO
                cannot load resource; throw an exception */
            }

            std::pair<std::unordered_map<GLenum, std::string>, std::string> info = it->second;

            std::unordered_map<GLenum, Texture*> materialTextures; // let's find textures
            for (auto& texInfo : info.first) {
                Texture* pTexture = getTexturePtr(texInfo.second);
                if (pTexture == nullptr) { // not loaded, load it
                    load(TEXTURE, texInfo.second);
                    pTexture = getTexturePtr(texInfo.second);
                }

                materialTextures.emplace(texInfo.first, pTexture);
            }

            Shader* pShader = getShaderPtr(info.second); // and shader too
            if (pShader == nullptr) {
                load(SHADER, info.second);
                pShader = getShaderPtr(info.second);
            }

            std::unique_ptr<Material> pMaterial = make_unique<Material>(materialTextures, pShader);

            materials[id] = std::move(pMaterial);
        }
    break;

    case MESH:
        {
            auto it = meshInfos.find(id);
            if (it == meshInfos.end()) {
                /*
                TODO
                cannot load resource; throw an exception */
            }

            Material* pMaterial = getMaterialPtr(it->second);
            if (pMaterial == nullptr) {
                load(MATERIAL, it->second);
                pMaterial = getMaterialPtr(it->second);
            }

            std::unique_ptr<Mesh> pMesh = make_unique<Mesh>(pMaterial);

            if (id == "sphere")
                Test::makeUVSphere(pMesh->getVBO(), pMesh->getIBO(), pMesh->getVAO(), pMesh->getNIndices(), 32, 16);

            meshes[id] = std::move(pMesh);
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
