#ifndef EVENT_THREAD_HH
#define EVENT_THREAD_HH


#include <thread>


class Device;


class EventThread {
public:
    EventThread(Device& device);
    EventThread(const EventThread&) = delete; //Ro3
    ~EventThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    EventThread& operator=(const EventThread&) = delete; //Ro3

private:
    Device& device;
    std::thread thread;
    bool running;
};


#endif // EVENT_THREAD_HH
