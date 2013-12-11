#ifndef RESOURCE_THREAD_HH
#define RESOURCE_THREAD_HH

#include "resources.hh"
#include "resource_loader.hh"

#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <tbb/tbb.h>

class Device;


class ResourceThread{
public:
    struct ResourceLoadCall{
        ResourceLoader* pResLoader;
        void (ResourceLoader::*pLoadFunc)(ResourceType, std::string);
        ResourceType resType;
        std::string resID;
    };

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
};


#endif // RESOURCE_THREAD_HH
