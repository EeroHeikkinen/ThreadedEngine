#ifndef PHYSICS_THREAD_HH
#define PHYSICS_THREAD_HH


#include <thread>
#include <btBulletDynamicsCommon.h>
#include <chrono>

#include "physics_tree.hh"
#include "component.hh"
#include "physics_motion_state.hh"

class Device;

class PhysicsThread {
public:
    PhysicsThread(Device&);
    PhysicsThread(const PhysicsThread&) = delete; //Ro3
    ~PhysicsThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);


    PhysicsTree* getPhysicsTree() const;

    PhysicsThread& operator=(const PhysicsThread&) = delete; //Ro3

    btDiscreteDynamicsWorld* getDynamicsWorld() const;

private:
    std::thread thread;
    bool running;
    PhysicsTree* physicsTree;

    //Bullet stuff

    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;

    btSequentialImpulseConstraintSolver* solver;

    btDiscreteDynamicsWorld* dynamicsWorld;

    typedef std::chrono::high_resolution_clock clock;
    std::chrono::time_point<clock> time_physics_prev, time_physics_curr;
    
};



#endif // PHYSICS_THREAD_HH
