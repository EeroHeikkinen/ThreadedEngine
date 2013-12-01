#ifndef DEVICE_HH
#define DEVICE_HH


#include "render_thread.hh"
#include "logic_thread.hh"
#include "physics_thread.hh"
#include "resource_thread.hh"
#include "scene_graph.hh"

#include <mutex>
#include <condition_variable>


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

    friend void RenderThread::init(void);
    friend void LogicThread::init(void);
    friend void PhysicsThread::init(void);
    friend void ResourceThread::init(void);

    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;

private:
    Device(void); // private constructor
    std::mutex initMutex;
    std::condition_variable initCV;
    /*
    ID of last successfully initialized thread
    RenderThread: 1
    PhysicsThread: 2
    ResourceThread: 3
    LogicThread: 4
    */
    unsigned int initThreadID;

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
