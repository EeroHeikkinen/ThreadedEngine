#ifndef THREADING_UTILS_HH
#define THREADING_UTILS_HH

#include <mutex>
#include <condition_variable>
#include <tbb/tbb.h>


class FunctionSequencer{
public:
    FunctionSequencer(void) : currentNumber(1){}

    template<typename Function>
    void runInSequence(Function func, unsigned int orderNumber){
        std::unique_lock<std::mutex> lock(mutex);
        while(currentNumber != orderNumber)
            cv.wait(lock);
        func();
        ++currentNumber;
        cv.notify_all();
    }
protected:
    std::mutex mutex;
    std::condition_variable cv;
    unsigned int currentNumber;
};

/* TODO: MAKE SURE THIS IS BASIC LOCKABLE *
 * if this is the case, this one can and  *
 * should be used with lock wrappers such *
 * as std::lock_guard or std::unique_lock */
class QueuedInterruptMutex{
public:
    QueuedInterruptMutex(void);

    //for owner thread to use
    void gainOwnership(void);
    bool checkInterrupts(void);
    void dispatchInterrupts(void);

    //for other threads to use
    void lock(void);
    void unlock(void);
private:
    std::mutex mutex;
    std::unique_lock<std::mutex> ownerLock;
    std::condition_variable ownerCv;
    std::unique_lock<std::mutex>* pCurrentLock;
    std::condition_variable* pCurrentCv;
    tbb::concurrent_queue<std::condition_variable*> cvQueue;
};

class InitSequencer : private FunctionSequencer{
public:
    InitSequencer(){}

    template<typename Thread>
    void initialize(Thread* pThread, unsigned int orderNumber){
        runInSequence([pThread](){pThread->init();}, orderNumber);
    }
};


#endif // THREADING_UTILS_HH
