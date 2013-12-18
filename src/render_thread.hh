#ifndef RENDER_THREAD_HH
#define RENDER_THREAD_HH

#include "renderer.hh"
#include "threading_utils.hh"

#include <thread>
#include <unordered_map>
#include <SFML/Window.hpp>

class Device;


class RenderThread{
public:
    RenderThread(Device*, unsigned int);
    ~RenderThread(void);
    RenderThread(const RenderThread&) = delete;
    RenderThread& operator=(const RenderThread&) = delete;

    void launch(unsigned int);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    // gains ownership of and adds a renderer pointer to vpRenderers vector.
    template<typename DerivedRenderer>
    DerivedRenderer* addRenderer(std::unique_ptr<DerivedRenderer>);

    // deletion has to be implemented carefully, as it's not a thread-safe operation
    // void deleteRenderer(Renderer*);
private:
    Device& device;
    std::thread thread;
    bool running;

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
