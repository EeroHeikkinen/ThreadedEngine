#ifndef TEST_ENTITIES_HH
#define TEST_ENTITIES_HH


#include "component.hh"
#include "shader.hh"
#include "texture.hh"

#include <GL/GLEW.h>
#include <glm/glm.hpp>
#include <mutex>


class Mesh;


namespace Test{

    class Camera : public LogicComponent {
    public:
        Camera(void);

        void logic(void);

        const glm::mat4& getViewMatrix(void) const;
        const glm::mat4& getProjectionMatrix(void) const;

    protected:
        float angle;
        glm::vec3 pos;
        glm::mat4 view, projection;
    };


    class SingleMeshEntity : public RenderComponent {
    public:
        SingleMeshEntity(Mesh* pMesh_, glm::mat4 model_);
        void render(const glm::mat4&, const glm::mat4&);
    private:
        Mesh* pMesh;
        glm::mat4 model;
    };

    class Sphere; //forward declaration for WatcherCamera
    class Box;
    class WatcherCamera : public Camera{
    public:
        WatcherCamera(Sphere* pSphere);
        WatcherCamera(Box* pBox);

        void logic(void);
    private:
        Sphere* pSphere;
        Box* pBox;
    };


    class Sphere : public RenderComponent,
                   public PhysicsComponent{
    public:
        Sphere(btCollisionShape* collisionMesh_,
               PhysicsNode* parent_,
               glm::vec3 initialPos_,
               glm::vec3 initialVel_,
               float mass_,
               float restitution_);
        ~Sphere(void);

        void render(const glm::mat4&, const glm::mat4&);


        glm::vec3 getPosition(void);
    private:
        GLuint VBO, IBO, VAO;
        Shader shader;
        unsigned int numIndices;
        glm::mat4 model;
    };


    class Box : public RenderComponent,
                public PhysicsComponent{
    public:
        Box(float xSize_, float ySize_, float zSize_,
            btCollisionShape* collisionMesh_,
            PhysicsNode* parent_,
            glm::vec3 initialPos_,
            glm::vec3 initialVel_,
            float mass_,
            float restitution_);
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
