#ifndef LOGIC_THREAD_HH
#define LOGIC_THREAD_HH


#include <thread>


class Device;


class LogicThread {
public:
    LogicThread(Device& device);
    LogicThread(const LogicThread&) = delete; //Ro3
    ~LogicThread(void);

    void launch(void);
    void stop(void);
    void join(void);

    void init(void);
    void loop(void);

    LogicThread& operator=(const LogicThread&) = delete; //Ro3

private:
    Device& device;
    std::thread thread;
    bool running;
};


#endif // LOGIC_THREAD_HH
