#ifndef RENDER_THREAD_HH
#define RENDER_THREAD_HH

#include "renderer.hh"

#include <thread>
#include <mutex>
#include <vector>
#include <SFML/Window.hpp>
class Device;


class RenderThread{
public:
    RenderThread(Device&);
    ~RenderThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    sf::Window* getWindowPtr(void);
    bool isWindowInitialized(void);

    // Deactivates the GL context from this thread and activates it on
    // the calling thread. This can happen only after rendering cycle.
    // Render thread will wait for the other thread to attach the
    // context back.
    void detachContext(void);
    void attachContext(void);

    // Adds a new Renderer pointer to vpRenderers vector.
    void addRenderer(Renderer*);
    void deleteRenderer(Renderer*);

    RenderThread(const RenderThread&) = delete;
    RenderThread& operator=(const RenderThread&) = delete;
private:
    std::thread thread;
    bool running;

    sf::ContextSettings settings;
    sf::Window* pWindow;
    bool windowInitialized;

    bool deactivatingContext;
    std::mutex glContextMutex;

    std::vector<Renderer*> vpRenderers;
};


#endif // RENDER_THREAD_HH
