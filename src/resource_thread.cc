#include "resource_thread.hh"
#include "device.hh"

#include <SFML/Window.hpp>
#include <iostream>//TEMP


ResourceThread::ResourceThread(Device& device_) :
    running(true)
    {
        thread = std::thread(&ResourceThread::launch, this);
    }

ResourceThread::~ResourceThread(void){
    if (running){
        running = false;
        thread.join();
    }

    delete pTestRenderer;//TEMP
    delete pCamera;//TEMP
    delete pSphere;//TEMP
    delete pBox1;//TEMP
    delete pBox2;//TEMP
    delete pBox3;//TEMP
}

void ResourceThread::launch(void){
    //New thread begins here
    init();
    while (running)
        loop();
}

void ResourceThread::stop(void){
    running = false;
}

void ResourceThread::join(void){
    thread.join();
}

void ResourceThread::init(void){
    std::lock_guard<std::mutex> lock(Device::getDevice().mutex);
    std::cout << "resInitBegin" << std::endl;
    while (!Device::getDevice().isGlewInitialized())
        sf::sleep(sf::milliseconds(5));
    //Begin of TEMP
    Device::getDevice().getRenderThread().detachContext();

    auto root = Device::getDevice().getPhysicsThread().getPhysicsTree().getRoot();

    pBox1 = new Test::Box(1.0f, 0.5f, 1.0f,
                         new btBoxShape(btVector3(1.0f, 0.5f, 1.0f)),
                         root,
                         glm::vec3(4.0f, -0.25f, 0.0f),
                         glm::vec3(0,0,0),
                         0, 0.4);

    pBox2 = new Test::Box(1.0f, 0.5f, 1.0f,
                         new btBoxShape(btVector3(1.0f, 0.5f, 1.0f)),
                         root,
                         glm::vec3(5.0f, 2.0f, 0.0f),
                         glm::vec3(0,0,0),
                         1.0, 1.0);

    pBox3 = new Test::Box(1.0f, 0.5f, 1.0f,
                         new btBoxShape(btVector3(1.0f, 0.5f, 1.0f)),
                         root,
                         glm::vec3(-4.0f, -0.25f, 0.0f),
                         glm::vec3(0,0,0),
                         0.0, 1.0);

    pSphere = new Test::Sphere(new btSphereShape(1),
                               root,
                               glm::vec3(-4.0f, 2.0f, 0.0f),
                               glm::vec3(0.0f, 4.0f, 0.0f),
                               1.0, 1.0);

    pCamera = new Test::Camera();
    pTestRenderer = new Test::TestRenderer(pCamera);

    Device::getDevice().getRenderThread().attachContext();
    Device::getDevice().resInitReady = true;
    Device::getDevice().CV.notify_all();
    std::cout << "resInitEnd" << std::endl;
    //End of TEMP
}

void ResourceThread::loop(void){
    sf::sleep(sf::milliseconds(250));

    /*
    TODO:
    Improve the delay
    */
}
