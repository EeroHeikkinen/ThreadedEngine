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

} // namespace Test


#endif // TEST_ENTITIES_HH
