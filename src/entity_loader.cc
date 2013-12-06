#include "entity_loader.hh"
#include "device.hh"


void EntityLoader::pushEntities(void) {
    DEVICE.getRenderThread().addRenderers(vpRenderers);
    DEVICE.getSceneGraph().addRenderComponents(vpRenderComponents);
    /*
    TODO
    phusics too
    */
    DEVICE.getLogicThread().addLogicComponents(vpLogicComponents);

    vpRenderers.clear();
    vpRenderComponents.clear();
    vpPhysicsComponents.clear();
    vpLogicComponents.clear();
}

void EntityLoader::addRenderer(Renderer* pRenderer) {
    vpRenderers.push_back(pRenderer);
}

void EntityLoader::addComponent(RenderComponent* pComponent) {
    vpRenderComponents.push_back(pComponent);
}

void EntityLoader::addComponent(PhysicsComponent* pComponent) {
    vpPhysicsComponents.push_back(pComponent);
}

void EntityLoader::addComponent(LogicComponent* pComponent) {
    vpLogicComponents.push_back(pComponent);
}
