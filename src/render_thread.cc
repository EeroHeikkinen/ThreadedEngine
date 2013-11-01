#include "render_thread.hh"

#include <iostream> //temp


RenderThread::RenderThread(void) :
    running(true) {
    thread = std::thread(&RenderThread::launch, this);
}

RenderThread::~RenderThread(void) {
    if (running) {
        running = false;
        thread.join();
    }
}

void RenderThread::launch(void) {
    //New thread begins here
    init();
    while (running)
        loop();
}

void RenderThread::stop(void) {
    running = false;
    thread.join();
}

void RenderThread::init(void) {
    std::cout << "Helloes from RenderThread!" << std::endl;//temp
}

void RenderThread::loop(void) {
    std::cout << "render ";//temp
}
