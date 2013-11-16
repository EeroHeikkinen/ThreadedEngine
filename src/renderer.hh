#ifndef RENDERER_HH
#define RENDERER_HH


class Renderer {
public:
    Renderer(void) { }
    Renderer(const Renderer&) = delete; // Ro3
    virtual ~Renderer(void) { }

    virtual void render(void) = 0;

    Renderer& operator=(const Renderer&) = delete; // Ro3
};


#endif // RENDERER_HH
