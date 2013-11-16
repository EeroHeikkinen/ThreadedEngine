#ifndef DEVICE_HH
#define DEVICE_HH


#include "render_thread.hh"
#include "logic_thread.hh"
#include "physics_thread.hh"
#include "resource_thread.hh"
#include "scene_graph.hh"

#include <mutex>


class Device {
public:
    Device(const Device&) = delete;
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

    // scene graph
    SceneGraph sceneGraph;
};


#endif // DEVICE_HH
