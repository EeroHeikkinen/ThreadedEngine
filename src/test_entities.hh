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
        ~Camera(void);

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
    };
/*
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
    */
} // namespace Test


#endif // TEST_ENTITIES_HH
