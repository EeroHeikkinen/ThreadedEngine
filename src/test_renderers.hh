#ifndef TEST_RENDERERS_HH
#define TEST_RENDERERS_HH

#include "renderer.hh"
#include "threading_utils.hh"
#include <tbb/concurrent_unordered_set.h>


namespace Test
{
    class Camera;//forward declaration for StupidRenderer

    class StupidRenderer : public Renderer{
    public:
        StupidRenderer(void);
        ~StupidRenderer(void);

        //Traversal...
        void render(void);
        //and growing are thread-safe, but...
        void addRenderComponent(RenderComponent* renderComponent){
            spRenderComponents.insert(renderComponent);
        }
        //removal isn't. Thus we need a more complicated approach.
        void removeRenderComponent(RenderComponent* renderComponent){
        }



    private:
        QueuedInterruptMutex erasureMutex;
        tbb::concurrent_unordered_set<RenderComponent*> spRenderComponents;
        Test::Camera* pCamera;
        std::unique_ptr<> defaultCamera;
    };
}


#endif // TEST_RENDERERS_HH
