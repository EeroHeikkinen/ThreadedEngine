#ifndef TEST_RENDERERS_HH
#define TEST_RENDERERS_HH

#include "renderer.hh"
#include "component.hh"

#include <tbb/concurrent_unordered_set.h>
#include <mutex>


namespace Test
{
    class Camera;//forward declaration for StupidRenderer

    class StupidRenderer : public Renderer{
    public:
        StupidRenderer(void);
        ~StupidRenderer(void){}

        void render(void);

        void addComponent(StupidRenderComponent*);
        void removeComponent(StupidRenderComponent*);

        void addComponent(StupidCameraComponent*);
        void removeComponent(StupidCameraComponent*);
    private:
        std::mutex mutex; //slow, but then again, this is StupidRenderer
        tbb::concurrent_unordered_set<StupidRenderComponent*> spStupidRenderComponents;

        glm::mat4 defaultView, defaultProj;
        StupidCameraComponent defaultCamera;

        StupidCameraComponent* pCurrentCamera;
    };
} //namespace Test


#endif // TEST_RENDERERS_HH
