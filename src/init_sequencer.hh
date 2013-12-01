#ifndef INIT_SEQUENCER_HH
#define INIT_SEQUENCER_HH

#include <mutex>
#include <condition_variable>
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


#endif // INIT_SEQUENCER_HH
