#include "device.hh"


int main(void)
{
    DEVICE.eventLoop();
    DEVICE.join();

    return 0;
}
