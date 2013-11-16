#ifndef COMPONENT_HH
#define COMPONENT_HH


#include <glm/gtc/matrix_transform.hpp>


class RenderComponent {
public:
    RenderComponent(void);
    RenderComponent(const RenderComponent&) = delete;
    virtual ~RenderComponent(void);

    virtual void render(const glm::mat4&, const glm::mat4&) = 0;

    RenderComponent& operator=(const RenderComponent&) = delete;
};


class LogicComponent {
public:
    LogicComponent(void);
    LogicComponent(const LogicComponent&) = delete;
    virtual ~LogicComponent(void);

    virtual void logic(void) = 0;

    LogicComponent& operator=(const LogicComponent&) = delete;
};


class PhysicsComponent {
public:
    PhysicsComponent(void) { };
    PhysicsComponent(const PhysicsComponent&) = delete;
    virtual ~PhysicsComponent(void) { };

    void calculate(void);

    PhysicsComponent& operator=(const PhysicsComponent&) = delete;
};


#endif // COMPONENT_HH
