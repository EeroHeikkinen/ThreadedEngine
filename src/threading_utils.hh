#ifndef THREADING_UTILS_HH
#define THREADING_UTILS_HH

#include <mutex>
#include <condition_variable>
#include <tbb/tbb.h>


class InitSequencer{
public:
    InitSequencer(void) : currentNumber(1){}

    template<unsigned int orderNumber, typename Thread>
    void initialize(Thread* thread){
        std::unique_lock<std::mutex> lock(mutex);
        while(currentNumber < orderNumber)
            cv.wait(lock);
        thread->init();
        ++currentNumber;
        cv.notify_all();
    }
private:
    std::mutex mutex;
    std::condition_variable cv;
    unsigned int currentNumber;
};

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


#endif // THREADING_UTILS_HH
