#ifndef RESOURCE_THREAD_HH
#define RESOURCE_THREAD_HH

#include "resources.hh"
#include "resource_loader.hh"
#include "test_entity_loaders.hh"//TEMP
#include "test_resource_loaders.hh"//TEMP

#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <tbb/tbb.h>


class Device;


class ResourceThread{
public:
    typedef std::pair<
                std::pair<ResourceLoader*, void (ResourceLoader::*)(ResourceType, std::string)>,
                std::pair<ResourceType, std::string> >
        ResourceLoadCall;

    ResourceThread(Device&);
    ~ResourceThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    void addResourceLoader(ResourceLoader* pResLoader);
    void pushResourceLoadCall(ResourceLoadCall loadCall);

    ResourceThread(const ResourceThread&) = delete;
    ResourceThread& operator=(const ResourceThread&) = delete;

private:
    std::thread thread;
    bool running;

    std::mutex resourceLoaderMutex;
    tbb::concurrent_vector<ResourceLoader*> vpResourceLoaders;

    //resource loader callback queue
    tbb::concurrent_queue<ResourceLoadCall> qLoadCalls;

    Test::TestEntityLoader* testEntLoader;//temp
    Test::TestResourceLoader* testResLoader;//temp
};


#endif // RESOURCE_THREAD_HH
