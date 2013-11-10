#ifndef RESOURCE_THREAD_HH
#define RESOURCE_THREAD_HH


#include <thread>


class Device;


class ResourceThread {
public:
    ResourceThread(Device& device);
    ResourceThread(const ResourceThread&) = delete; //Ro3
    ~ResourceThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    ResourceThread& operator=(const ResourceThread&) = delete; //Ro3

private:
    Device& device;
    std::thread thread;
    bool running;
};


#endif // RESOURCE_THREAD_HH
