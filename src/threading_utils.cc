#include "threading_utils.hh"
#include <iostream>


//InitSequencer
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
    while(!physicsInitialized)
        cv.wait(lock);
    (thread->*init)();
    resourceInitialized = true;
    cv.notify_all();
}

void InitSequencer::logicThread(LogicThread* thread, void (LogicThread::*init)(void)){
    std::unique_lock<std::mutex> lock(mutex);
    while(!resourceInitialized)
        cv.wait(lock);
    (thread->*init)();
    logicInitialized = true;
    cv.notify_all();
}

//QueuedInterruptMutex
QueuedInterruptMutex::QueuedInterruptMutex(void) : //initialize QIM
    interruptLockPtr(nullptr),
    notifiedCvPtr(nullptr)
    {}

void QueuedInterruptMutex::own(void){
    ownerLock = std::unique_lock<std::mutex>(mutex);
}

bool QueuedInterruptMutex::checkInterrupts(void){ //check if there are any interrupts waiting
    return !cvQueue.empty();
}

void QueuedInterruptMutex::dispatchInterrupts(void){ //dispatch waiting interrupts
    std::cout << "Dispatching" << std::endl;
    if(cvQueue.empty())
        return;

    if(!cvQueue.try_pop(notifiedCvPtr)){ //if not empty, pop the CV to be notified
            /*TODO
            throw an exception */
            return;
    }
    notifiedCvPtr->notify_all(); //notify it
    while(notifiedCvPtr != &ownerCv) //stop execution until the queue is empty
        ownerCv.wait(ownerLock);
}

void QueuedInterruptMutex::lock(void){
    std::cout << "Locking" << std::endl;
    std::condition_variable* cvPtr = new std::condition_variable;
    cvQueue.push(cvPtr);

    std::unique_lock<std::mutex>* lockPtr = new std::unique_lock<std::mutex>(mutex);
    while(notifiedCvPtr != cvPtr)
        cvPtr->wait(*lockPtr);
    interruptLockPtr = lockPtr; //storing the lock pointer into a member variable for transfer into unlock call
}

void QueuedInterruptMutex::unlock(void){
    std::cout << "Unlocking" << std::endl;

    delete notifiedCvPtr; //this destructs the lock-call-specific condition variable
    if(!cvQueue.try_pop(notifiedCvPtr))
        notifiedCvPtr = &ownerCv;
    notifiedCvPtr->notify_all();
    delete interruptLockPtr; //this destructs the unique_lock and unlocks the mutex
}
