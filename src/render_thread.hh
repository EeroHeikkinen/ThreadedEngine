#ifndef RENDER_THREAD_HH
#define RENDER_THREAD_HH

#include "renderer.hh"
#include "threading_utils.hh"

#include <thread>
#include <mutex>
#include <unordered_map>
#include <SFML/Window.hpp>

class Device;


class RenderThread{
public:
    RenderThread(Device*, unsigned int);
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

    // Gains ownership of and adds a renderer pointer to vpRenderers vector.
    template<typename DerivedRenderer>
    DerivedRenderer* addRenderer(std::unique_ptr<DerivedRenderer>);

    void addRenderers(tbb::concurrent_vector<Renderer*>&);

    //deletion has to be implemented carefully, as it's not a thread-safe operation
    //void deleteRenderer(Renderer*);

    RenderThread(const RenderThread&) = delete;
    RenderThread& operator=(const RenderThread&) = delete;
private:
    // Thread
    std::thread thread;
    bool running;
    unsigned int initOrderNumber;

    // Window & context
    sf::ContextSettings settings;
    sf::Window* pWindow;
    bool windowInitialized;
    QueuedInterruptMutex glContextMutex;

    // Renderer container vector
    std::mutex rendererMapMutex;
    std::unordered_map<Renderer*, std::unique_ptr<Renderer>> mpRenderers;
};

template<typename DerivedRenderer>
DerivedRenderer* RenderThread::addRenderer(std::unique_ptr<DerivedRenderer> pRenderer){
    std::lock_guard<std::mutex> lock(rendererMapMutex);
    DerivedRenderer* pAdded = pRenderer.get();
    if(pAdded == nullptr)
        return nullptr;

    mpRenderers.emplace(pAdded, std::move(pRenderer));
    return pAdded;
}


#endif // RENDER_THREAD_HH
