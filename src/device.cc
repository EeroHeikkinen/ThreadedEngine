#include "device.hh"


Device::Device(void) :
    renderThread(*this),
    eventThread(*this),
    physicsThread(*this) { }

void Device::join(void) {
    renderThread.join();
    eventThread.join();
    physicsThread.join();
}

void Device::stop(void) {
    renderThread.stop();
    eventThread.stop();
    physicsThread.stop();
}

RenderThread& Device::getRenderThread(void) {
    return renderThread;
}
