#include "resource_loader.hh"
#include "device.hh"


void ResourceLoader::pushResources(void) {
    Device::getDevice().getRenderThread().addRenderers(vpRenderers);
    Device::getDevice().getSceneGraph().addRenderComponents(vpRenderComponents);
    /*
    TODO
    phusics too
    */
    Device::getDevice().getLogicThread().addLogicComponents(vpLogicComponents);

    vpRenderers.clear();
    vpRenderComponents.clear();
    vpPhysicsComponents.clear();
    vpLogicComponents.clear();
}

void ResourceLoader::addRenderer(Renderer* pRenderer) {
    vpRenderers.push_back(pRenderer);
}

void ResourceLoader::addComponent(RenderComponent* pComponent) {
    vpRenderComponents.push_back(pComponent);
}

void ResourceLoader::addComponent(PhysicsComponent* pComponent) {
    vpPhysicsComponents.push_back(pComponent);
}

void ResourceLoader::addComponent(LogicComponent* pComponent) {
    vpLogicComponents.push_back(pComponent);
}
