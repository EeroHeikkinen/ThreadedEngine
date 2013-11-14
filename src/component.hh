#ifndef COMPONENT_HH
#define COMPONENT_HH


class RenderComponent {
public:
    RenderComponent(void);
    RenderComponent(const RenderComponent&) = delete;
    virtual ~RenderComponent(void);

    void render(void);

    RenderComponent& operator=(const RenderComponent&) = delete;
};


class PhysicsComponent {
public:
    PhysicsComponent();
    PhysicsComponent(const PhysicsComponent&) = delete;
    virtual ~PhysicsComponent();

    void calculate();

    PhysicsComponent& operator=(const PhysicsComponent&) = delete;
};

#endif // COMPONENT_HH
