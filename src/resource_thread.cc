#include "resource_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>
#include <iostream>


ResourceThread::ResourceThread(Device* pDevice, unsigned int initOrderNumber) :
    device(*pDevice),
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
    device.initSequencer.initialize(this, initOrderNumber);
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
    std::lock_guard<GlContextMutex> lock(device.glContextMutex);

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

    pResLoader->setShaderObjectInfo("VS_texture_normal", "res/shaders/VS_texture_normal.glsl",
                                    GL_VERTEX_SHADER);
    pResLoader->setShaderObjectInfo("FS_texture_normal", "res/shaders/FS_texture_normal.glsl",
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
    StandardResourceLoader* pResLoader2 =
        addResourceLoader(std::move(pResLoader),
                          std::vector<ResourceType>{TEXTURE, // resource types to associate it with
                                                    SHADER_OBJECT,
                                                    SHADER,
                                                    MATERIAL,
                                                    MESH});
    // load 'em
    pResLoader2->load(MESH, "sphere");
    pResLoader2->load(MESH, "box");
    pResLoader2->load(MATERIAL, "material_edwerd");
    pResLoader2->load(MATERIAL, "material_grassblock");
}

void ResourceThread::loop(void){
    while(!qLoadCalls.empty()){
        std::lock_guard<GlContextMutex> lock(device.glContextMutex);

        ResourceLoadCall call;
        if (qLoadCalls.try_pop(call))
            call.pResLoader->load(call.resType, call.resId);
    }

    sf::sleep(sf::milliseconds(10));

    /*
    TODO:
    Improve the delay
    */
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
