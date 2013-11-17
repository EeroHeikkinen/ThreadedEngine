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
        float angle;
        glm::vec3 pos;
        glm::mat4 view, projection;
    };


    class Sphere :
    public RenderComponent,
    public PhysicsComponent {
    public:
        Sphere(
               btCollisionShape* collisionMesh_,
               PhysicsNode* parent,
               glm::vec3 pos,
               float mass_
               );
        ~Sphere(void);

        void render(const glm::mat4&, const glm::mat4&);

    private:
        GLuint VBO, IBO, VAO;
        Shader shader;
        unsigned int numIndices;
        glm::mat4 model;
    };


    class Box :
    public RenderComponent {
    public:
        Box(float xSize, float ySize, float zSize, glm::vec3 pos);
        ~Box(void);

        void render(const glm::mat4&, const glm::mat4&);

    private:
        GLuint VBO, IBO, VAO;
        Shader shader;
        unsigned int numIndices;
        glm::mat4 model;
    };

} // namespace test


#endif // TEST_ENTITIES_HH
