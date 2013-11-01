#ifndef RENDER_THREAD_HH
#define RENDER_THREAD_HH


#include <thread>


class RenderThread {
public:
    RenderThread(void);
    RenderThread(const RenderThread&) = delete; //Ro3
    ~RenderThread(void);

    void launch(void);
    void stop(void);

    void init(void);
    void loop(void);

    RenderThread& operator=(const RenderThread&) = delete; //Ro3
private:
    std::thread thread;
    bool running;
};


#endif // RENDER_THREAD_HH
