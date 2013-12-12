#ifndef PHYSICS_THREAD_HH
#define PHYSICS_THREAD_HH

#include "physics_tree.hh"
#include "component.hh"
#include "physics_utils.hh"

#include <thread>
#include <btBulletDynamicsCommon.h>
#include <chrono>

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

    PhysicsTree& getPhysicsTree() const;
    DiscreteDynamicsWorld& getDynamicsWorld() const;

    PhysicsThread(const PhysicsThread&) = delete;
    PhysicsThread& operator=(const PhysicsThread&) = delete;
private:
    std::thread thread;
    bool running;

    std::unique_ptr<PhysicsTree> pPhysicsTree;

    //Bullet stuff
    std::unique_ptr<btBroadphaseInterface> pBroadphase;
    std::unique_ptr<btSequentialImpulseConstraintSolver> pSolver;
    std::unique_ptr<btDefaultCollisionConfiguration> pCollisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> pDispatcher;
    std::unique_ptr<DiscreteDynamicsWorld> pDynamicsWorld;

    typedef std::chrono::high_resolution_clock clock;
    std::chrono::time_point<clock> time_prev, time_curr;
};


#endif // PHYSICS_THREAD_HH
