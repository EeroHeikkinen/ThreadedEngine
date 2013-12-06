#ifndef DEVICE_HH
#define DEVICE_HH


#include "render_thread.hh"
#include "logic_thread.hh"
#include "physics_thread.hh"
#include "resource_thread.hh"
#include "scene_graph.hh"
#include "threading_utils.hh"

#define DEVICE Device::getDevice()

class Device{
public:
    static Device& getDevice(void);

    void eventLoop(void);
    void stop(void);
    void join(void);

    void setGlewInitialized(bool);
    bool isGlewInitialized(void) const;

    RenderThread& getRenderThread(void);
    LogicThread& getLogicThread(void);
    PhysicsThread& getPhysicsThread(void);

    SceneGraph& getSceneGraph(void);

    friend void RenderThread::launch(void);
    friend void PhysicsThread::launch(void);
    friend void ResourceThread::launch(void);
    friend void LogicThread::launch(void);

    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;

private:
    Device(void); // private constructor

    InitSequencer initSequencer;


    // flags
    bool glewInitialized;
    bool running;

    // threads
    RenderThread renderThread;
    PhysicsThread physicsThread;
    ResourceThread resourceThread;
    LogicThread logicThread;

    // scene graph
    SceneGraph sceneGraph;
};


#endif // DEVICE_HH
