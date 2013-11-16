#include "logic_thread.hh"

#include <SFML/Window.hpp>


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

}

void LogicThread::loop(void) {
    // render
    for (auto it = vpLogicComponents.begin(); it != vpLogicComponents.end(); it++) {
        (*it)->logic();
    }

    sf::sleep(sf::milliseconds(10));
    /*
        TODO:
        Improve the delay
    */
}

void LogicThread::addLogicComponent(LogicComponent* pLogicComponent) {
    vpLogicComponents.push_back(pLogicComponent);
}

void LogicThread::deleteLogicComponent(LogicComponent* pLogicComponent) {
    for (auto it = vpLogicComponents.begin(); it != vpLogicComponents.end(); it++) {
        if (*it == pLogicComponent) {
            vpLogicComponents.erase(it);
            return;
        }
    }
}
