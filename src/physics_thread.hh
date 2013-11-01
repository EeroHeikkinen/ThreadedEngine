#ifndef PHYSICS_THREAD_HH
#define PHYSICS_THREAD_HH


#include <thread>


class PhysicsThread {
public:
    PhysicsThread(void);
    PhysicsThread(const PhysicsThread&) = delete; //Ro3
    ~PhysicsThread(void);

    void launch(void);
    void stop(void);

    void init(void);
    void loop(void);

    PhysicsThread& operator=(const PhysicsThread&) = delete; //Ro3
private:
    std::thread thread;
    bool running;
};


#endif // PHYSICS_THREAD_HH
