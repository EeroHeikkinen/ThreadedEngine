#ifndef TEST_ENTITIES_HH
#define TEST_ENTITIES_HH

#include "component.hh"
#include "shader.hh"
#include "texture.hh"

#include <GL/GLEW.h>
#include <glm/glm.hpp>
#include <mutex>


namespace Test{

    class Camera : public LogicComponent{
    public:
        Camera(void);

        virtual void logic(void);

        const glm::mat4& getViewMatrix(void) const;
        const glm::mat4& getProjectionMatrix(void) const;
    protected:
        float angle;
        glm::vec3 pos;
        glm::mat4 view, projection;
    };


    class Sphere : public RenderComponent{
    public:
        Sphere(glm::mat4 model_);
        ~Sphere(void);

        void render(const glm::mat4&, const glm::mat4&);

        glm::vec3 getPosition(void);
    private:
        GLuint VBO, IBO, VAO;
        Shader shader;
        unsigned int numIndices;
        glm::mat4 model;
        Texture texture;
    };


    class Box : public RenderComponent{
    public:
        Box(float xSize_, float ySize_, float zSize_, glm::mat4 model_);
        ~Box(void);

        void render(const glm::mat4&, const glm::mat4&);
    private:
        GLuint VBO, IBO, VAO;
        Shader shader;
        unsigned int numIndices;
        glm::mat4 model;
    };

} // namespace Test


#endif // TEST_ENTITIES_HH
