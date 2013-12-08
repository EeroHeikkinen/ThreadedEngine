#ifndef PHYSICS_THREAD_HH
#define PHYSICS_THREAD_HH

#include "physics_tree.hh"
#include "component.hh"
#include "physics_motion_state.hh"

#include <thread>
#include <btBulletDynamicsCommon.h>
#include <chrono>
class Device;


class PhysicsThread{
public:
    PhysicsThread(Device*, unsigned int);
    ~PhysicsThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    PhysicsTree& getPhysicsTree() const;
    btDiscreteDynamicsWorld& getDynamicsWorld() const;

    PhysicsThread(const PhysicsThread&) = delete;
    PhysicsThread& operator=(const PhysicsThread&) = delete;
private:
    std::thread thread;
    bool running;
    unsigned int initOrderNumber;
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
