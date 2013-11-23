#ifndef RESOURCE_LOADER_HH
#define RESOURCE_LOADER_HH


#include <tbb/tbb.h>
#include <iostream>


class Renderer;
class RenderComponent;
class PhysicsComponent;
class LogicComponent;


class ResourceLoader {
public:
    ResourceLoader(void) {}
    virtual ~ResourceLoader(void) {}

    // Pushes loaded resources from internal storage to specified data containers
    void pushResources(void);

protected:
    // Inherited class implementations will use these functions to add resources
    void addRenderer(Renderer*);
    void addComponent(RenderComponent*);
    void addComponent(PhysicsComponent*);
    void addComponent(LogicComponent*);
    // For the lazy ones:
    template <typename T>
    void addEntity(T pEntity) {
        RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(pEntity);
        if (pRenderComponent)
            addComponent(pRenderComponent);

        PhysicsComponent* pPhysicsComponent = dynamic_cast<PhysicsComponent*>(pEntity);
        if (pPhysicsComponent)
            addComponent(pPhysicsComponent);

        LogicComponent* pLogicComponent = dynamic_cast<LogicComponent*>(pEntity);
        if (pLogicComponent)
            addComponent(pLogicComponent);
    }

private:
    tbb::concurrent_vector<Renderer*> vpRenderers;
    tbb::concurrent_vector<RenderComponent*> vpRenderComponents;
    tbb::concurrent_vector<PhysicsComponent*> vpPhysicsComponents;
    tbb::concurrent_vector<LogicComponent*> vpLogicComponents;
};


#endif // RESOURCE_LOADER_HH
