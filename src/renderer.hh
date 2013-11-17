#ifndef RENDERER_HH
#define RENDERER_HH


class Renderer{
public:
    Renderer(void){}
    virtual ~Renderer(void){}

    virtual void render(void) = 0;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
};


#endif // RENDERER_HH
