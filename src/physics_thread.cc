#include "physics_thread.hh"

#include <iostream> //temp


PhysicsThread::PhysicsThread(Device& device) :
    device(device), running(true) {
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
    thread.join();
}

void PhysicsThread::join(void) {
    thread.join();
}

void PhysicsThread::init(void) {
    std::cout << "Helloes from PhysicsThread!" << std::endl;//temp
    // TEMP: creating arbitrary tree consisting of one physics component for testing purposes
    PhysicsComponent* component = new PhysicsComponent;
    for (unsigned i = 0; i < 5; i++) {
        auto parent = physicsTree.getRoot();
        for (unsigned j = 0; j < 6; j++) {
            parent = physicsTree.addNode(parent, component);
        }
    }
    // end of TEMP
}

void PhysicsThread::loop(void) {
    std::cout << "physics ";//temp

    PhysicsNode* root = physicsTree.getRoot();
    iterateTree(root);

}
// Iterates the tree consisting of physics components, calls calculate-function for each
// component and recursively calls iterateTree for each of current node's children.
void PhysicsThread::iterateTree(PhysicsNode* node) {
    for (auto child : node->getChildren()) {
        child->getComponent()->calculate();
        iterateTree(child);
    }
}