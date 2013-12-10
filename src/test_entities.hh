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
class Material;
namespace Test{class StupidRenderer;}


namespace Test{
    class Camera : public Entity{
    public:
        Camera(StupidRenderer*);

        void logic(void);
    protected:
        float angle;
        glm::vec3 pos;
        glm::mat4 view, proj;
    };

    class SingleMeshEntity : public Entity{
    public:
        SingleMeshEntity(StupidRenderer* pStupidRenderer,
                         Mesh* pMesh,
                         glm::mat4 model);

        void render(const glm::mat4&, const glm::mat4&);
    private:
        Mesh* pMesh;
        glm::mat4 model;
    };

    class Sphere : public Entity{ //render, physics
    public:
        Sphere(StupidRenderer* pStupidRenderer,
               std::unique_ptr<btCollisionShape> pCollisionMesh,
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
        Box(StupidRenderer* pStupidRenderer,
            float xHalfSize, float yHalfSize, float zHalfSize,
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

    class EdwerdCollection : public Entity{
    public:
        EdwerdCollection(void){}
        ~EdwerdCollection(void);

        void loadEdwerds(StupidRenderer*);
    private:
        Texture* pTexture;
        Shader* pShader;
        Material* pMaterial;
        Mesh* pMesh;
    };
} // namespace Test


#endif // TEST_ENTITIES_HH
