#ifndef DEVICE_HH
#define DEVICE_HH


#include "render_thread.hh"
#include "logic_thread.hh"
#include "physics_thread.hh"
#include "resource_thread.hh"

#include <mutex>


class Device {
public:
    Device(const Device&) = delete;
    static Device& getDevice(void);

    void eventLoop(void);
    void stop(void);
    void join(void);

    RenderThread& getRenderThread(void);
    LogicThread& getLogicThread(void);
    PhysicsThread& getPhysicsThread(void);

    void setGlewInitialized(bool);
    bool isGlewInitialized(void) const;

    Device& operator=(const Device&) = delete;

private:
    Device(void); // private constructor
    std::mutex mutex;

    // flags
    bool glewInitialized;
    bool running;

    // threads
    RenderThread renderThread;
    LogicThread logicThread;
    PhysicsThread physicsThread;
    ResourceThread resourceThread;
};


#endif // DEVICE_HH
