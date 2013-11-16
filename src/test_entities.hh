#ifndef TEST_ENTITIES_HH
#define TEST_ENTITIES_HH


#include "component.hh"
#include "shader.hh"

#include <GL/GLEW.h>
#include <glm/glm.hpp>


namespace test {

    class Camera :
    public LogicComponent {
    public:
        Camera(void);

        void logic(void);

        const glm::mat4& getViewMatrix(void) const;
        const glm::mat4& getProjectionMatrix(void) const;

    private:
        glm::vec3 pos;
        glm::mat4 view, projection;
    };


    class Triangle :
    public RenderComponent,
    public LogicComponent {
    public:
        Triangle(void);
        ~Triangle(void);

        void render(const glm::mat4&, const glm::mat4&);
        void logic(void);

    private:
        GLuint VBO, IBO, VAO;
        Shader shader;

        float alpha;
        glm::vec3 pos;
    };

} // namespace test


#endif // TEST_ENTITIES_HH
