#ifndef LOGIC_THREAD_HH
#define LOGIC_THREAD_HH


#include "component.hh"

#include <thread>
#include <vector>


class Device;


class LogicThread {
public:
    LogicThread(Device& device);
    LogicThread(const LogicThread&) = delete; //Ro3
    ~LogicThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    LogicThread& operator=(const LogicThread&) = delete; //Ro3

    // Adds a new LogicComponent pointer to vpLogicComponents vector.
    void addLogicComponent(LogicComponent*);
    // Seeks for given LogicComponent pointer and if found, deletes it.
    // Automagically called by LogicComponent's destructor.
    void deleteLogicComponent(LogicComponent*);

private:
    Device& device;
    std::thread thread;
    bool running;

    std::vector<LogicComponent*> vpLogicComponents;
};


#endif // LOGIC_THREAD_HH
