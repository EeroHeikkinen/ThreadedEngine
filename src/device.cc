#include "device.hh"


Device::Device(void) {
    renderThread.launch();
    logicThread.launch();
    physicsThread.launch();
    resourceThread.launch();
    eventThread.launch();
}
