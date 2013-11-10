#include "logic_thread.hh"

#include <iostream> //temp


LogicThread::LogicThread(Device& device) :
    device(device),
    running(true) {
    thread = std::thread(&LogicThread::launch, this);
}

LogicThread::~LogicThread(void) {
    if (running) {
        running = false;
        thread.join();
    }
}

void LogicThread::launch(void) {
    //New thread begins here
    init();
    while (running)
        loop();
}

void LogicThread::stop(void) {
    running = false;
}

void LogicThread::join(void) {
    thread.join();
}

void LogicThread::init(void) {
    std::cout << "Helloes from LogicThread!" << std::endl;//temp
}

void LogicThread::loop(void) {
    std::cout << "logic ";//temp
}
