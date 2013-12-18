#ifndef LOGIC_THREAD_HH
#define LOGIC_THREAD_HH

#include <thread>
#include <unordered_set>

class Device;
class LogicComponent;


class LogicThread{
public:
    LogicThread(Device*, unsigned int);
    ~LogicThread(void);
    LogicThread(const LogicThread&) = delete;
    LogicThread& operator=(const LogicThread&) = delete;

    void launch(unsigned int);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    // Adds a new LogicComponent pointer to vpLogicComponents vector.
    void addComponent(LogicComponent* pComponent);
    void removeComponent(LogicComponent* pComponent);
private:
    Device& device;
    std::thread thread;
    bool running;

    std::unordered_set<LogicComponent*> spLogicComponents;
    LogicComponent *pCurrentComponent, *pToBeErased;
};


#endif // LOGIC_THREAD_HH
