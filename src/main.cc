#include "device.hh"


int main()
{
    Device::getDevice();
    Device::getDevice().eventLoop();
    Device::getDevice().join();

    return 0;
}
