#ifndef PHYSICS_THREAD_HH
#define PHYSICS_THREAD_HH


#include <thread>
#include "physics_tree.hh"
#include "component.hh"

class Device;

class PhysicsThread {
public:
    PhysicsThread(Device& device);
    PhysicsThread(const PhysicsThread&) = delete; //Ro3
    ~PhysicsThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    void iterateTree(PhysicsNode*);

    PhysicsTree* getTree() const;

    PhysicsThread& operator=(const PhysicsThread&) = delete; //Ro3
private:
    Device& device;
    std::thread thread;
    bool running;
    PhysicsTree* physicsTree;
};



#endif // PHYSICS_THREAD_HH
