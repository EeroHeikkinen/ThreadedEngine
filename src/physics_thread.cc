#include "physics_thread.hh"
#include "physics_tree.hh"
#include "device.hh"

#include <SFML/Window.hpp>
#include <iostream>


PhysicsThread::PhysicsThread(Device* pDevice, unsigned int initOrderNumber) :
    running(true)
    {
        thread = std::thread(&PhysicsThread::launch, this, initOrderNumber);
    }

PhysicsThread::~PhysicsThread(void){
    if (running){
        running = false;
        thread.join();
    }
}

void PhysicsThread::launch(unsigned int initOrderNumber){
    //New thread begins here
    DEVICE.initSequencer.initialize(this, initOrderNumber);
    while (running)
        loop();
}

void PhysicsThread::stop(void){
    running = false;
}

void PhysicsThread::join(void){
    thread.join();
}

void PhysicsThread::init(void){
    std::cout << "physicsinitBegin" << std::endl;
    pPhysicsTree = make_unique<PhysicsTree>();

    // very basic bullet configuration, change if needed!
    pBroadphase = make_unique<btDbvtBroadphase>();
    pSolver = make_unique<btSequentialImpulseConstraintSolver>();
    pCollisionConfiguration = make_unique<btDefaultCollisionConfiguration>();
    pDispatcher = make_unique<btCollisionDispatcher>(pCollisionConfiguration.get());
    pDynamicsWorld = make_unique<DiscreteDynamicsWorld>(pDispatcher.get(),
                                                        pBroadphase.get(),
                                                        pSolver.get(),
                                                        pCollisionConfiguration.get());

    pDynamicsWorld->setGravity(btVector3(0,-9.81,0));

    time_prev = clock::now();
    time_curr = clock::now();
    std::cout << "physicsinitEnd" << std::endl;
}

void PhysicsThread::loop(void){
    time_curr = clock::now();
    float duration =
        std::chrono::duration_cast<std::chrono::milliseconds>
            (time_curr - time_prev).count() / 1000.0;
    pDynamicsWorld->stepSimulation(duration, 10);
    time_prev = time_curr;
}

PhysicsTree& PhysicsThread::getPhysicsTree() const{
    return *pPhysicsTree;
}

DiscreteDynamicsWorld& PhysicsThread::getDynamicsWorld() const{
    return *pDynamicsWorld;
}
