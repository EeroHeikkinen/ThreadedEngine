#include "threading_utils.hh"

#include <SFML/Window.hpp>


//GlContextMutex
GlContextMutex::GlContextMutex(void) :
    windowExists(false),
    waitingThreads(0)
    {}

void GlContextMutex::lock(void){
    WaitCounter waitCounter(waitingThreads);
    mutex.lock();
    pWindow->setActive(true);
}

void GlContextMutex::unlock(void){
    pWindow->setActive(false);
    mutex.unlock();
}

sf::Window& GlContextMutex::getWindow(void){
    if(windowExists)
        return *pWindow;
    else
        throw "Trying to get nonexistent window";
}

unsigned int GlContextMutex::getWaitingThreads(void){
    return waitingThreads;
}

/*//QueuedInterruptMutex
QueuedInterruptMutex::QueuedInterruptMutex(void) : //initialize QIM
    pCurrentCv(nullptr)
    {}

void QueuedInterruptMutex::gainOwnership(void){
    ownerLock = std::unique_lock<std::mutex>(mutex);
}

bool QueuedInterruptMutex::checkInterrupts(void){ //check if there are any interrupts waiting
    return !cvQueue.empty();
}

void QueuedInterruptMutex::dispatchInterrupts(void){ //dispatch waiting interrupts
    if(cvQueue.empty())
        return;
    if(!cvQueue.try_pop(pCurrentCv)) //if not empty, pop the CV to be notified
        return;
    pCurrentCv->notify_all(); //notify it
    while(pCurrentCv != &ownerCv) //stop execution until the queue is empty
        ownerCv.wait(ownerLock);
}

void QueuedInterruptMutex::lock(void){
    std::condition_variable queuedCv;
    cvQueue.push(&queuedCv);

    std::unique_lock<std::mutex> queuedLock(mutex);
    while(pCurrentCv != &queuedCv)
        queuedCv.wait(queuedLock);
    currentLock = std::move(queuedLock); //storing the lock in a member variable for transfer into unlock call
}

void QueuedInterruptMutex::unlock(void){
    if(!cvQueue.try_pop(pCurrentCv)) //check if queue is empty
        pCurrentCv = &ownerCv;
    pCurrentCv->notify_all();
    currentLock.unlock(); //this unlocks the mutex (doesn't kill the crab)
}*/
