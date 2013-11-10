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


#endif // COMPONENT_HH
