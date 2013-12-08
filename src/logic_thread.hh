#ifndef LOGIC_THREAD_HH
#define LOGIC_THREAD_HH

#include "component.hh"

#include <thread>
#include <tbb/tbb.h>
class Device;


class LogicThread{
public:
    LogicThread(Device*, unsigned int);
    ~LogicThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    // Adds a new LogicComponent pointer to vpLogicComponents vector.
    void addLogicComponent(LogicComponent* pComponent);
    void addLogicComponents(tbb::concurrent_vector<LogicComponent*>& vpComponents);
    //void deleteLogicComponent(LogicComponent*);

    LogicThread(const LogicThread&) = delete;
    LogicThread& operator=(const LogicThread&) = delete;
private:
    std::thread thread;
    bool running;
    unsigned int initOrderNumber;

    tbb::concurrent_vector<LogicComponent*> vpLogicComponents;
};


#endif // LOGIC_THREAD_HH
