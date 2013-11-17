#ifndef RESOURCE_THREAD_HH
#define RESOURCE_THREAD_HH

#include "test_renderers.hh"//TEMP
#include "test_entities.hh"//TEMP

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

    Test::Camera* pCamera;//TEMP
    Test::TestRenderer* pTestRenderer;//TEMP
    Test::Sphere* pSphere;//TEMP
    Test::Box* pBox;//TEMP
};


#endif // RESOURCE_THREAD_HH
