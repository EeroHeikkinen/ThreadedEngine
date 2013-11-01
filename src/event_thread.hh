#ifndef EVENT_THREAD_HH
#define EVENT_THREAD_HH


#include <thread>


class EventThread {
public:
    EventThread(void);
    EventThread(const EventThread&) = delete; //Ro3
    ~EventThread(void);

    void launch(void);
    void stop(void);

    void init(void);
    void loop(void);

    EventThread& operator=(const EventThread&) = delete; //Ro3
private:
    std::thread thread;
    bool running;
};


#endif // EVENT_THREAD_HH
