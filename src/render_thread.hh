#ifndef RENDER_THREAD_HH
#define RENDER_THREAD_HH


#include "component.hh"
#include "test_entities.hh"//TEMP

#include <thread>
#include <mutex>
#include <vector>//TEMP?
#include <SFML/Window.hpp>


class Device;


class RenderThread {
public:
    RenderThread(Device& device);
    RenderThread(const RenderThread&) = delete; //Ro3
    ~RenderThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    RenderThread& operator=(const RenderThread&) = delete; //Ro3

    sf::Window* getWindowPtr(void);
    bool isWindowInitialized(void);
    // Asks to unload the GL context from this thread, can happen only
    // after rendering cycle.
    void detachContext(void);
    void attachContext(void);

    // Adds a new RenderComponent pointer to vpRenderComponents vector.
    void addRenderComponent(RenderComponent*);
    // Seeks for given RenderComponent pointer and if found, deletes it.
    // Automagically called by RenderComponent's destructor.
    void deleteRenderComponent(RenderComponent*);

private:
    Device& device;
    std::thread thread;
    bool running;

    sf::ContextSettings settings;
    sf::Window* pWindow;
    bool windowInitialized;
    bool deactivatingContext;
    std::mutex glContextMutex;

    std::vector<RenderComponent*> vpRenderComponents;//TEMP?
};


#endif // RENDER_THREAD_HH
