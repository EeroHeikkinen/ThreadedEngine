#ifndef THREADING_UTILS_HH
#define THREADING_UTILS_HH

#include "make_unique.hh"

#include <mutex>
#include <atomic>
#include <memory>
#include <condition_variable>

namespace sf{class Window;}


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

class GlContextMutex{
public:
    GlContextMutex(void);
    GlContextMutex(const GlContextMutex&) = delete;
    GlContextMutex& operator=(const GlContextMutex&) = delete;

    void lock(void);
    void unlock(void);

    template<typename... Args>
    void createWindow(Args... args);

    sf::Window& getWindow(void);
    unsigned int getWaitingThreads(void);
private:
    std::atomic_bool windowExists;
    std::unique_ptr<sf::Window> pWindow;

    std::mutex mutex;
    std::atomic_uint waitingThreads;
    class WaitCounter{
    public:
        WaitCounter(std::atomic_uint& N) : N(N) {++N;}
        ~WaitCounter(void){--N;}
    private:
        std::atomic_uint& N;
    };
};
template<typename... Args>
void GlContextMutex::createWindow(Args... args){
    pWindow = make_unique<sf::Window>(std::forward<Args>(args)...);
    windowExists = true;
}

class InitSequencer : private FunctionSequencer{
public:
    template<typename Thread>
    void initialize(Thread* pThread, unsigned int orderNumber){
        runInSequence([pThread](){pThread->init();}, orderNumber);
    }
};

/*class QueuedInterruptMutex{
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
    std::unique_lock<std::mutex> currentLock;
    std::condition_variable* pCurrentCv;
    tbb::concurrent_queue<std::condition_variable*> cvQueue;
};*/


#endif // THREADING_UTILS_HH
