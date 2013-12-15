#ifndef PHYSICS_THREAD_HH
#define PHYSICS_THREAD_HH

#include "physics_tree.hh"
#include "physics_utils.hh"

#include <thread>
#include <chrono>
#include <btBulletDynamicsCommon.h>

class Device;


class PhysicsThread{
public:
    PhysicsThread(Device*, unsigned int);
    ~PhysicsThread(void);

    void launch(unsigned int);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    PhysicsTree& getPhysicsTree();
    DiscreteDynamicsWorld& getDynamicsWorld();

    PhysicsThread(const PhysicsThread&) = delete;
    PhysicsThread& operator=(const PhysicsThread&) = delete;
private:
    std::thread thread;
    bool running;

    PhysicsTree physicsTree;

    //Bullet stuff
    btDbvtBroadphase broadphase;
    btSequentialImpulseConstraintSolver solver;
    btDefaultCollisionConfiguration collisionConfiguration;
    btCollisionDispatcher dispatcher;
    DiscreteDynamicsWorld dynamicsWorld;

    typedef std::chrono::high_resolution_clock clock;
    std::chrono::time_point<clock> time_prev, time_curr;
};


#endif // PHYSICS_THREAD_HH
