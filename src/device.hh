#ifndef DEVICE_HH
#define DEVICE_HH

#include "render_thread.hh"
#include "logic_thread.hh"
#include "physics_thread.hh"
#include "resource_thread.hh"
#include "threading_utils.hh"
#include "entity.hh"

#define DEVICE Device::getDevice()

class Device{
public:
    static Device& getDevice(void);
    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;

    void eventLoop(void);
    void stop(void);
    void join(void);

    RenderThread& getRenderThread(void);
    PhysicsThread& getPhysicsThread(void);
    ResourceThread& getResourceThread(void);
    LogicThread& getLogicThread(void);

    Entity& getUniverse(void);

    friend void RenderThread::launch(unsigned int);
    friend void PhysicsThread::launch(unsigned int);
    friend void ResourceThread::launch(unsigned int);
    friend void LogicThread::launch(unsigned int);

private:
    Device(void); // private constructor

    // initialization
    InitSequencer initSequencer;

    // flags
    bool running;

    // threads
    RenderThread renderThread;
    PhysicsThread physicsThread;
    ResourceThread resourceThread;
    LogicThread logicThread;

    // entity graph
    Entity universe;
};


#endif // DEVICE_HH
