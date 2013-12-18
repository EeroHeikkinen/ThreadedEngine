#ifndef RESOURCE_THREAD_HH
#define RESOURCE_THREAD_HH

#include "resources.hh"
#include "resource_loader.hh"

#include <forward_list>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <tbb/tbb.h>

class Device;


class ResourceThread{
public:
    ResourceThread(Device*, unsigned int);
    ~ResourceThread(void);
    ResourceThread(const ResourceThread&) = delete;
    ResourceThread& operator=(const ResourceThread&) = delete;

    void launch(unsigned int);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    template<typename DerivedLoader>
    DerivedLoader* addResourceLoader(std::unique_ptr<DerivedLoader>,
                                     std::vector<ResourceType>);

    void loadResource(ResourceType resType, const std::string& id = "");

    /*TODO: fix this interface*/
    ResourceLoader* getResourceLoaderPtr(ResourceType resType);
private:
    Device& device;
    std::thread thread;
    bool running;

    std::forward_list<std::unique_ptr<ResourceLoader>> lpResourceLoaders;

    //WHY THE HELL CAN'T I USE AN ENUM INSTEAD OF UINT HERE?!
    std::unordered_map<unsigned int, ResourceLoader*> mpResourceLoadersByType;

    struct ResourceLoadCall{
        ResourceLoader* pResLoader;
        ResourceType resType;
        std::string resId;
    };

    //resource loader callback queue
    tbb::concurrent_queue<ResourceLoadCall> qLoadCalls;
};


template<typename DerivedLoader>
DerivedLoader* ResourceThread::addResourceLoader(std::unique_ptr<DerivedLoader> pLoader,
                                                 std::vector<ResourceType> vTypes){
    DerivedLoader* pAdded = pLoader.get();

    lpResourceLoaders.emplace_front(std::move(pLoader));

    for(ResourceType type : vTypes)
        mpResourceLoadersByType[type] = pAdded;

    return pAdded;
}


#endif // RESOURCE_THREAD_HH
