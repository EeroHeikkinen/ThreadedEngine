#ifndef RESOURCE_THREAD_HH
#define RESOURCE_THREAD_HH

#include "test_resource_loaders.hh"//TEMP

#include <thread>
class Device;


class ResourceThread{
public:
    ResourceThread(Device&);
    ~ResourceThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    ResourceThread(const ResourceThread&) = delete;
    ResourceThread& operator=(const ResourceThread&) = delete;

private:
    std::thread thread;
    bool running;

    Test::TestResourceLoader* testResLoader;
};


#endif // RESOURCE_THREAD_HH
