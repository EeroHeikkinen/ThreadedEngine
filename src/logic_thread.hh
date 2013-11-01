#ifndef LOGIC_THREAD_HH
#define LOGIC_THREAD_HH


#include <thread>


class LogicThread {
public:
    LogicThread(void);
    LogicThread(const LogicThread&) = delete; //Ro3
    ~LogicThread(void);

    void launch(void);
    void stop(void);

    void init(void);
    void loop(void);

    LogicThread& operator=(const LogicThread&) = delete; //Ro3
private:
    std::thread thread;
    bool running;
};


#endif // LOGIC_THREAD_HH
