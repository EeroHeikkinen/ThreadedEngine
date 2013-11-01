#include "event_thread.hh"

#include <iostream> //temp


EventThread::EventThread(void) :
    running(true) {
    thread = std::thread(&EventThread::launch, this);
}

EventThread::~EventThread(void) {
    if (running) {
        running = false;
        thread.join();
    }
}

void EventThread::launch(void) {
    //New thread begins here
    init();
    while (running)
        loop();
}

void EventThread::stop(void) {
    running = false;
    thread.join();
}

void EventThread::init(void) {
    std::cout << "Helloes from EventThread!" << std::endl;//temp
}

void EventThread::loop(void) {
    std::cout << "event ";//temp
}
