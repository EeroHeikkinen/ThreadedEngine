#include "physics_thread.hh"

#include <SFML/Window.hpp>
#include <iostream> //temp


PhysicsThread::PhysicsThread(Device& device) :
    running(true) {
    thread = std::thread(&PhysicsThread::launch, this);
    physicsTree = new PhysicsTree;
}

PhysicsThread::~PhysicsThread(void) {
    if (running) {
        running = false;
        thread.join();
    }
    delete physicsTree;
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
    PhysicsNode* root = physicsTree->getRoot();
    iterateTree(root);

    sf::sleep(sf::milliseconds(10));
    /*
        TODO:
        Improve the delay
    */
}
// Iterates the tree consisting of physics components, calls calculate-function for each
// component and recursively calls iterateTree for each of current node's children.
void PhysicsThread::iterateTree(PhysicsNode* node) {
    for (auto child : node->getChildren()) {
        child->getComponent()->calculate();
        iterateTree(child);
    }
}

PhysicsTree* PhysicsThread::getTree() const {
    return physicsTree;
}
