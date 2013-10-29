#ifndef DEVICE_HH
#define DEVICE_HH


class Device {
public:
    Device(void);

private:
    RenderThread renderThread;
    LogicThread logicThread;
    PhysicsThread physicsThread;
    ResourceThread resourceThread;
    EventThread eventThread;
};


#endif // DEVICE_HH
