#ifndef COMPONENT_HH
#define COMPONENT_HH


class RenderComponent {
public:
    RenderComponent(void);
    RenderComponent(const RenderComponent&) = delete;
    virtual ~RenderComponent(void);

    virtual void render(void) { };

    RenderComponent& operator=(const RenderComponent&) = delete;
};


class LogicComponent {
public:
    LogicComponent(void);
    LogicComponent(const LogicComponent&) = delete;
    virtual ~LogicComponent(void);

    virtual void logic(void) { };

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
