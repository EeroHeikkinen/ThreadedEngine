#ifndef TEST_ENTITIES_HH
#define TEST_ENTITIES_HH


#include "component.hh"
#include "shader.hh"

#include <GL/GLEW.h>
#include <glm/glm.hpp>


namespace test {

    class TriangleRender : public RenderComponent {
    public:
        TriangleRender(void);
        ~TriangleRender(void) { };

        void render(void);

    private:
        GLuint VBO, IBO, VAO;
        Shader shader;
    };


    class TriangleLogic : public LogicComponent {
    public:
        TriangleLogic(void);
        ~TriangleLogic(void) { };

        void logic(void);
        glm::vec3 getPosition(void);

    private:
        float alpha;
        glm::vec3 pos;
    };


    class Triangle :
    public TriangleRender,
    public TriangleLogic {
    public:
        Triangle(void) { }
        ~Triangle(void) { }
    };

} // namespace test


#endif // TEST_ENTITIES_HH
