#ifndef LOGIC_THREAD_HH
#define LOGIC_THREAD_HH

#include "component.hh"
#include "test_entity_loaders.hh"//TEMP
#include "test_resource_loaders.hh"//TEMP

#include <thread>
#include <tbb/tbb.h>
class Device;


class LogicThread{
public:
    LogicThread(Device&);
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

    tbb::concurrent_vector<LogicComponent*> vpLogicComponents;

    Test::TestEntityLoader* testEntLoader;//temp
};


#endif // LOGIC_THREAD_HH
