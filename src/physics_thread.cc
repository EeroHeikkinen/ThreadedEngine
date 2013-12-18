#include "physics_thread.hh"
#include "device.hh"
#include "physics_utils.hh"

#include <iostream>

PhysicsThread::PhysicsThread(Device* pDevice, unsigned int initOrderNumber) :
    device(*pDevice),
    running(true),
    dispatcher(&collisionConfiguration),
    dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration)
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
    device.initSequencer.initialize(this, initOrderNumber);
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
    dynamicsWorld.setGravity(btVector3(0,-9.81,0));

    time_prev = clock::now();
    time_curr = clock::now();
}

void PhysicsThread::loop(void){
    time_curr = clock::now();
    float duration =
        std::chrono::duration_cast<std::chrono::milliseconds>
            (time_curr - time_prev).count() / 1000.0;
    dynamicsWorld.stepSimulation(duration, 10);
    time_prev = time_curr;
}

PhysicsTree& PhysicsThread::getPhysicsTree(){
    return physicsTree;
}

DiscreteDynamicsWorld& PhysicsThread::getDynamicsWorld(){
    return dynamicsWorld;
}
