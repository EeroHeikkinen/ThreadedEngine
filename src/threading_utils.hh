#ifndef THREADING_UTILS_HH
#define THREADING_UTILS_HH

#include <mutex>
#include <condition_variable>
#include <tbb/tbb.h>
class RenderThread;
class PhysicsThread;
class ResourceThread;
class LogicThread;


class InitSequencer{
public:
    InitSequencer(void);

    void renderThread(RenderThread*, void (RenderThread::*)(void));
    void physicsThread(PhysicsThread*, void (PhysicsThread::*)(void));
    void resourceThread(ResourceThread*, void (ResourceThread::*)(void));
    void logicThread(LogicThread*, void (LogicThread::*)(void));
private:
    std::mutex mutex;
    std::condition_variable cv;

    bool renderInitialized;
    bool physicsInitialized;
    bool resourceInitialized;
    bool logicInitialized;
};

class QueuedInterruptMutex{
public:
    QueuedInterruptMutex(void);

    //for owner thread to use
    void own(void);
    bool checkInterrupts(void);
    void dispatchInterrupts(void);

    //for other threads to use
    void lock(void);
    void unlock(void);
private:
    std::mutex mutex;
    std::unique_lock<std::mutex> ownerLock;
    std::condition_variable ownerCv;
    std::unique_lock<std::mutex>* interruptLockPtr;
    std::condition_variable* notifiedCvPtr;
    tbb::concurrent_queue<std::condition_variable*> cvQueue;
};


#endif // THREADING_UTILS_HH
