#include "device.hh"


int main()
{
    DEVICE;
    DEVICE.eventLoop();
    DEVICE.join();

    return 0;
}
