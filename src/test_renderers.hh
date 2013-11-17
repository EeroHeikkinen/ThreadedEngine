#ifndef TEST_RENDERERS_HH
#define TEST_RENDERERS_HH

#include "renderer.hh"

class SceneGraph;


namespace Test{
        class Camera;//forward declaration for TestRenderer
    class TestRenderer : public Renderer{
    public:
        TestRenderer(Camera*);
        ~TestRenderer(void);

        void render(void);
    private:
        SceneGraph& sceneGraph;
        Test::Camera* pCamera;
    };
}


#endif // TEST_RENDERERS_HH
