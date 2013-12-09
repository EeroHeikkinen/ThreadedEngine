#ifndef LOGIC_THREAD_HH
#define LOGIC_THREAD_HH

#include "component.hh"

#include <thread>
#include <unordered_set>
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
    void addComponent(LogicComponent* pComponent);
    void removeComponent(LogicComponent* pComponent);

    LogicThread(const LogicThread&) = delete;
    LogicThread& operator=(const LogicThread&) = delete;
private:
    std::thread thread;
    bool running;
    unsigned int initOrderNumber;

    std::unordered_set<LogicComponent*> spLogicComponents;
    LogicComponent *pCurrentComponent, *pToBeErased;
};


#endif // LOGIC_THREAD_HH
