#include "init_sequencer.hh"


InitSequencer::InitSequencer() :
    renderInitialized(false),
    physicsInitialized(false),
    resourceInitialized(false),
    logicInitialized(false)
    {}

void InitSequencer::renderThread(RenderThread* thread, void (RenderThread::*init)(void)){
    std::unique_lock<std::mutex> lock(mutex);
    (thread->*init)();
    renderInitialized = true;
    cv.notify_all();
}

void InitSequencer::physicsThread(PhysicsThread* thread, void (PhysicsThread::*init)(void)){
    std::unique_lock<std::mutex> lock(mutex);
    while(!renderInitialized)
        cv.wait(lock);
    (thread->*init)();
    physicsInitialized = true;
    cv.notify_all();
}

void InitSequencer::resourceThread(ResourceThread* thread, void (ResourceThread::*init)(void)){
    std::unique_lock<std::mutex> lock(mutex);
    while(!renderInitialized || !physicsInitialized) //render too just to be sure
        cv.wait(lock);
    (thread->*init)();
    resourceInitialized = true;
    cv.notify_all();
}

void InitSequencer::logicThread(LogicThread* thread, void (LogicThread::*init)(void)){
    std::unique_lock<std::mutex> lock(mutex);
    while(!renderInitialized || !physicsInitialized || !resourceInitialized)
        cv.wait(lock);
    (thread->*init)();
    logicInitialized = true;
    cv.notify_all();
}

