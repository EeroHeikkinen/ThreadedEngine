#include "physics_thread.hh"

#include <iostream> //temp


PhysicsThread::PhysicsThread(Device& device) :
    device(device),
    running(true) {
    thread = std::thread(&PhysicsThread::launch, this);
}

PhysicsThread::~PhysicsThread(void) {
    if (running) {
        running = false;
        thread.join();
    }
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
    std::cout << "Helloes from PhysicsThread!" << std::endl;//temp
}

void PhysicsThread::loop(void) {
    std::cout << "physics ";//temp
}
