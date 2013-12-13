#include "resource_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>


ResourceThread::ResourceThread(Device* pDevice, unsigned int initOrderNumber) :
    running(true)
    {
        thread = std::thread(&ResourceThread::launch, this, initOrderNumber);
    }

ResourceThread::~ResourceThread(void){
    if (running){
        running = false;
        thread.join();
    }
}

void ResourceThread::launch(unsigned int initOrderNumber){
    //New thread begins here
    DEVICE.initSequencer.initialize(this, initOrderNumber);
    while (running)
        loop();
}

void ResourceThread::stop(void){
    running = false;
}

void ResourceThread::join(void){
    thread.join();
}

void ResourceThread::init(void){
    // ptr
    std::unique_ptr<StandardResourceLoader> pResLoader = make_unique<StandardResourceLoader>();

    // infoes
    pResLoader->setTextureInfo("edwerd", "res/textures/edwerd.png",
                               Texture::TYPE_IMG,
                               GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR,
                               GL_WRAP_BORDER, GL_WRAP_BORDER, 4);

    pResLoader->setTextureInfo("grassblock", "res/textures/grassblock.png",
                               Texture::TYPE_IMG,
                               GL_NEAREST, GL_NEAREST,
                               GL_WRAP_BORDER, GL_WRAP_BORDER, 2);

    pResLoader->setShaderObjectInfo("VS_texture_normal", "res/shaders/VS_LSD.glsl",
                                    GL_VERTEX_SHADER);
    pResLoader->setShaderObjectInfo("FS_texture_normal", "res/shaders/FS_LSD.glsl",
                                    GL_FRAGMENT_SHADER);
    pResLoader->setShaderProgramInfo("texture_normal",
                                     std::vector<std::string> {"VS_texture_normal",
                                                               "FS_texture_normal"});

    pResLoader->setMaterialInfo("material_edwerd",
                                std::unordered_map<GLenum, std::string>
                                    {std::make_pair(GL_TEXTURE0, "edwerd")},
                                "texture_normal");

    pResLoader->setMaterialInfo("material_grassblock",
                                std::unordered_map<GLenum, std::string>
                                    {std::make_pair(GL_TEXTURE0, "grassblock")},
                                "texture_normal");

    //add it
    addResourceLoader(std::move(pResLoader),
                      std::vector<ResourceType>{TEXTURE, // resource types to associate it with
                                                SHADER_OBJECT,
                                                SHADER,
                                                MATERIAL,
                                                MESH});

    // load 'em
    loadResource(MESH, "sphere");
    loadResource(MESH, "box");
    loadResource(MATERIAL, "material_edwerd");
    loadResource(MATERIAL, "material_grassblock");
}

void ResourceThread::loop(void){
    while(!qLoadCalls.empty()){
        DEVICE.getRenderThread().detachContext();

            ResourceLoadCall call;
            if (qLoadCalls.try_pop(call))
                call.pResLoader->load(call.resType, call.resId);

        DEVICE.getRenderThread().attachContext();
    }

    sf::sleep(sf::milliseconds(10));

    /*
    TODO:
    Improve the delay
    */
}

void ResourceThread::addResourceLoader(std::unique_ptr<ResourceLoader> pLoader,
                                       std::vector<ResourceType> vTypes){
    for(ResourceType type : vTypes)
        mpResourceLoadersByType[type] = pLoader.get();

    lpResourceLoaders.emplace_front(std::move(pLoader));
}

void ResourceThread::loadResource(ResourceType resType, const std::string& resId){
    auto it = mpResourceLoadersByType.find(resType);
    if(it != mpResourceLoadersByType.end()){
        ResourceLoadCall call = {it->second, resType, resId};
        qLoadCalls.push(call);
    }
    else{/* TODO: throw an exception */}
}

ResourceLoader* ResourceThread::getResourceLoaderPtr(ResourceType resType){
    auto it = mpResourceLoadersByType.find(resType);
    if (it == mpResourceLoadersByType.end())
        return nullptr;
    return it->second;
}
