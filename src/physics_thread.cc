#include "physics_thread.hh"
#include "physics_tree.hh"

#include <SFML/Window.hpp>
#include <iostream> //temp


PhysicsThread::PhysicsThread(Device& device) :
    running(true) {
    thread = std::thread(&PhysicsThread::launch, this);
}

PhysicsThread::~PhysicsThread(void) {
    if (running) {
        running = false;
        thread.join();
    }

    delete physicsTree;
    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;

}

void PhysicsThread::launch(void) {
    //New thread begins here
    init();
    while (running)
        loop();

}

void PhysicsThread::stop(void) {
    running = false;
}

void PhysicsThread::join(void) {
    thread.join();
}

void PhysicsThread::init(void) {

    physicsTree = new PhysicsTree;

    // very basic bullet configuration, change if needed!
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0,-9.81,0));

    time_physics_prev = clock::now();
    time_physics_curr = clock::now();
    // TEMP: creating arbitrary tree consisting of one physics component for testing purposes
    /*PhysicsComponent* component = new PhysicsComponent;
    for (unsigned i = 0; i < 5; i++) {
        auto parent = physicsTree->getRoot();
        for (unsigned j = 0; j < 6; j++) {
            parent = physicsTree->addNode(parent, component);
        }
    }*/
    // end of TEMP
}

void PhysicsThread::loop(void) {
    //std::cout << "physics ";//temp
    time_physics_curr = clock::now();
    dynamicsWorld->stepSimulation((float)(std::chrono::duration_cast<std::chrono::milliseconds>(
                                        time_physics_curr - time_physics_prev).count()) / 1000.0, 10);
    time_physics_prev = time_physics_curr;
}


PhysicsTree* PhysicsThread::getPhysicsTree() const {
    return physicsTree;
}

btDiscreteDynamicsWorld* PhysicsThread::getDynamicsWorld() const {
    return dynamicsWorld;
}
