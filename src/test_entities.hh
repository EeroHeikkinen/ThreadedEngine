#ifndef TEST_ENTITIES_HH
#define TEST_ENTITIES_HH

#include "entity.hh"
#include "component.hh"
#include "shader.hh"
#include "texture.hh"

#include <GL/GLEW.h>
#include <glm/glm.hpp>
#include <mutex>
#include <chrono>

class Mesh;
class Material;
namespace Test{class StupidRenderer;}


namespace Test{
    class Camera : public Entity{
    public:
        Camera(StupidRenderer*);
        ~Camera(void);

        void logic(void);
    protected:
        float angle;
        glm::vec3 pos;
        glm::mat4 view, proj;

        typedef std::chrono::high_resolution_clock clock;
        std::chrono::time_point<clock> time_prev, time_curr;
    };

    class SingleMeshEntity : public Entity{
    public:
        SingleMeshEntity(StupidRenderer* pStupidRenderer,
               Mesh* pMesh,
               Material* pMaterial,
               glm::mat4 model);
        virtual ~SingleMeshEntity(void);

        void render(const glm::mat4&, const glm::mat4&);
    protected:
        Mesh* pMesh;
        Material* pMaterial;
        glm::mat4 model;
    };

    class Edwerd : public SingleMeshEntity{
    public:
        Edwerd(StupidRenderer* pStupidRenderer,
               glm::mat4 model);
    };

    class Sphere : public SingleMeshEntity{
    public:
        Sphere(StupidRenderer* pStupidRenderer,
               float radius,
               Material* pMaterial,
               glm::vec3 initialPos,
               glm::vec3 initialVel,
               float mass,
               float restitution);
        ~Sphere(void);
    private:
        glm::mat4 scale;
    };


    class Box : public SingleMeshEntity{
    public:
        Box(StupidRenderer* pStupidRenderer,
            float xHalfSize, float yHalfSize, float zHalfSize,
            Material* pMaterial,
            glm::vec3 initialPos,
            glm::vec3 initialVel,
            float mass,
            float restitution);
        ~Box(void);
    private:
        glm::mat4 scale;
    };

    class EdwerdCollection : public Entity{
    public:
        EdwerdCollection(StupidRenderer*);
    };

    class World : public Entity{
    public:
        World(StupidRenderer*);
        virtual ~World(void);

        void logic(void);
    private:
        StupidRenderer* pRenderer;
        typedef std::chrono::high_resolution_clock clock;
        std::chrono::time_point<clock> time_prev, time_curr;
    };
} // namespace Test


#endif // TEST_ENTITIES_HH
