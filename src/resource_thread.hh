#ifndef RESOURCE_THREAD_HH
#define RESOURCE_THREAD_HH

#include "resources.hh"
#include "resource_loader.hh"

#include <forward_list>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <tbb/tbb.h>

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

    void addResourceLoader(std::unique_ptr<ResourceLoader>,
                           std::vector<ResourceType>);

    void loadResource(ResourceType resType, const std::string& id = "");

    ResourceThread(const ResourceThread&) = delete;
    ResourceThread& operator=(const ResourceThread&) = delete;

private:
    std::thread thread;
    bool running;

    std::forward_list<std::unique_ptr<ResourceLoader>> lpResourceLoaders;
    std::mutex resourceLoaderMutex;

    //WHY THE FUCK CAN'T I USE AN ENUM INSTEAD OF UINT HERE?!
    std::unordered_map<unsigned int, ResourceLoader*> mpResourceLoadersByType;

    struct ResourceLoadCall{
        ResourceLoader* pResLoader;
        ResourceType resType;
        std::string resId;
    };

    //resource loader callback queue
    tbb::concurrent_queue<ResourceLoadCall> qLoadCalls;
};


#endif // RESOURCE_THREAD_HH
