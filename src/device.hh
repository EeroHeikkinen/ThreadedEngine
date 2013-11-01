#ifndef DEVICE_HH
#define DEVICE_HH


#include "render_thread.hh"
#include "logic_thread.hh"
#include "event_thread.hh"
#include "physics_thread.hh"
#include "resource_thread.hh"


class Device {
private:
    RenderThread renderThread;
    LogicThread logicThread;
    EventThread eventThread;
    PhysicsThread physicsThread;
    ResourceThread resourceThread;
};


#endif // DEVICE_HH
