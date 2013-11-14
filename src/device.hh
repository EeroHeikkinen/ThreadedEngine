#ifndef DEVICE_HH
#define DEVICE_HH


#include "render_thread.hh"
#include "logic_thread.hh"
#include "physics_thread.hh"
#include "resource_thread.hh"


class Device {
public:
    Device(void);
    Device(const Device&) = delete;

    void join(void);
    void stop(void);

    RenderThread& getRenderThread(void);

    Device& operator=(const Device&) = delete;

private:
    RenderThread renderThread;
    //LogicThread logicThread;
    //PhysicsThread physicsThread;
    //ResourceThread resourceThread;

    void eventLoop(void);
    bool running;
};


#endif // DEVICE_HH
