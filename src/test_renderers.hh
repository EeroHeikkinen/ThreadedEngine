#ifndef TEST_RENDERERS_HH
#define TEST_RENDERERS_HH


#include "renderer.hh"


class SceneGraph;


namespace test {

    class Camera;


    class TestRenderer : public Renderer {
    public:
        TestRenderer(test::Camera*);
        ~TestRenderer(void);

        void render(void);

    private:
        SceneGraph& sceneGraph;
        test::Camera* pCamera;
    };

}


#endif // TEST_RENDERERS_HH
