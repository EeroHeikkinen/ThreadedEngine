#include "threading_utils.hh"


//QueuedInterruptMutex
QueuedInterruptMutex::QueuedInterruptMutex(void) : //initialize QIM
    pCurrentLock(nullptr),
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
    std::condition_variable* pQueuedCv = new std::condition_variable;
    cvQueue.push(pQueuedCv);

    std::unique_lock<std::mutex>* pQueuedLock = new std::unique_lock<std::mutex>(mutex);
    while(pCurrentCv != pQueuedCv)
        pQueuedCv->wait(*pQueuedLock);
    pCurrentLock = pQueuedLock; //storing the lock pointer into a member variable for transfer into unlock call
}

void QueuedInterruptMutex::unlock(void){
    delete pCurrentCv; //this destructs the queued condition variable
    if(!cvQueue.try_pop(pCurrentCv)) //check if queue is empty
        pCurrentCv = &ownerCv;
    pCurrentCv->notify_all();
    delete pCurrentLock; //this destructs the unique_lock and unlocks the mutex
}
