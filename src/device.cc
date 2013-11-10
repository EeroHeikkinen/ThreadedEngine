#include "device.hh"


Device::Device(void) :
    renderThread(*this),
    eventThread(*this) { }

void Device::join(void) {
    renderThread.join();
    eventThread.join();
}

void Device::stop(void) {
    renderThread.stop();
    eventThread.stop();
}

RenderThread& Device::getRenderThread(void) {
    return renderThread;
}
