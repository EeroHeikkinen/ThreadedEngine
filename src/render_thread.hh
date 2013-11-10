#ifndef RENDER_THREAD_HH
#define RENDER_THREAD_HH


#include <thread>
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

    sf::Window& getWindow(void);

private:
    Device& device;
    std::thread thread;
    bool running;

    sf::Window window;
    sf::ContextSettings settings;
};


#endif // RENDER_THREAD_HH
