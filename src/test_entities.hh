#ifndef TEST_ENTITIES_HH
#define TEST_ENTITIES_HH

#include "entity.hh"
#include "component.hh"
#include "shader.hh"
#include "texture.hh"

#include <GL/GLEW.h>
#include <glm/glm.hpp>
#include <mutex>

class Mesh;


namespace Test{
    class Camera : public Entity{
    public:
        Camera(Test::StupidRenderer*);

        void logic(void);
    protected:
        float angle;
        glm::vec3 pos;
        glm::mat4 view, proj;
    };

    class SingleMeshEntity : public Entity{
    public:
        SingleMeshEntity(Mesh* pMesh, glm::mat4 model);

        void render(const glm::mat4&, const glm::mat4&);
    private:
        Mesh* pMesh;
        glm::mat4 model;
    };

    class Sphere : public Entity{ //render, physics
    public:
        Sphere(std::unique_ptr<btCollisionShape> pCollisionMesh,
               PhysicsNode* pParent,
               glm::vec3 initialPos,
               glm::vec3 initialVel,
               float mass,
               float restitution);
        ~Sphere(void);

        void render(const glm::mat4&, const glm::mat4&);

        glm::vec3 getPosition(void);
    private:
        GLuint VBO, IBO, VAO;
        Shader shader;
        unsigned int numIndices;
        glm::mat4 model;
    };


    class Box : public Entity{ //render, physics
    public:
        Box(float xHalfSize, float yHalfSize, float zHalfSize,
            std::unique_ptr<btCollisionShape> pCollisionMesh,
            PhysicsNode* pParent,
            glm::vec3 initialPos,
            glm::vec3 initialVel,
            float mass,
            float restitution);
        ~Box(void);

        void render(const glm::mat4&, const glm::mat4&);

        glm::vec3 getPosition(void);
    private:
        GLuint VBO, IBO, VAO;
        Shader shader;
        unsigned int numIndices;
        glm::mat4 model;
    };

} // namespace Test


#endif // TEST_ENTITIES_HH
