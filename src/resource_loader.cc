#include "resource_loader.hh"
#include "device.hh"


void ResourceLoader::loadResource(ResourceType resType, const std::string& id) {
    DEVICE.getResourceThread().pushResourceLoadCall(
        std::make_pair(
            std::make_pair(this, &ResourceLoader::load),
            std::make_pair(resType, id)
        )
    );
}


StandardResourceLoader::~StandardResourceLoader(void) {
    for (auto i : textures)
        delete i.second;

    for (auto i : shaders)
        delete i.second;

    for (auto i : materials)
        delete i.second;

    for (auto i : meshes)
        delete i.second;
}

Texture* StandardResourceLoader::getTexturePtr(const std::string& id) const {
    if (id != "") {
        auto it = textures.find(id);
        if (it != textures.end())
            return it->second;
    }
    return nullptr;
}

Shader* StandardResourceLoader::getShaderPtr(const std::string& id) const {
    if (id != "") {
        auto it = shaders.find(id);
        if (it != shaders.end())
            return it->second;
    }
    return nullptr;
}

Material* StandardResourceLoader::getMaterialPtr(const std::string& id) const {
    if (id != "") {
        auto it = materials.find(id);
        if (it != materials.end())
            return it->second;
    }
    return nullptr;
}

Mesh* StandardResourceLoader::getMeshPtr(const std::string& id) const {
    if (id != "") {
        auto it = meshes.find(id);
        if (it != meshes.end())
            return it->second;
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

void StandardResourceLoader::load(ResourceType resType, std::string id) {
    std::lock_guard<std::mutex> lock(mutex);

    switch (resType) {
    case TEXTURE_IMG:
        try {
            std::pair<std::string, Texture::Info> info = textureInfos.at(id);
            Texture* pTexture =
                new Texture(info.second.minFilter, info.second.magFilter,
                            info.second.sWrap, info.second.tWrap, info.second.AFLevel);
            pTexture->loadFromFile(info.first);
        }
        catch (const std::out_of_range& oor) {
            return;
        }
        return;
    break;

    case INVALID_TYPE:
        return;
    break;

    default:
        return;
    break;
    }
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
