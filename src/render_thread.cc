#include "render_thread.hh"
#include "device.hh"

#include <GL/GLEW.h>
#include <SFML/OpenGL.hpp>
#include <iostream>


RenderThread::RenderThread(Device* pDevice, unsigned int initOrderNumber) :
    device(*pDevice),
    running(true)
    {
        // window settings
        sf::ContextSettings settings;
        settings.depthBits = 24;
        settings.stencilBits = 8;
        settings.antialiasingLevel = 4;
        settings.majorVersion = 3;
        settings.minorVersion = 3;

        // create the window
        device.glContextMutex.createWindow(sf::VideoMode(1280, 960),
                                           "OpenGL",
                                           sf::Style::Default,
                                           settings);
        device.glContextMutex.getWindow().setVerticalSyncEnabled(true);

        // initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK) // TODO: throw exception in case of failure
            std::cout << "GLEW initialization failed." << std::endl;//TEMP

        // disable GL context for main thread (re-enabling it in RenderThread::join)
        device.glContextMutex.getWindow().setActive(false);

        // launch render thread
        thread = std::thread(&RenderThread::launch, this, initOrderNumber);
    }

RenderThread::~RenderThread(void){
    if (running){
        running = false;
        thread.join();
    }
}

void RenderThread::launch(unsigned int initOrderNumber){
    // gain ownership of the GL context
    std::lock_guard<GlContextMutex> lock(device.glContextMutex);

    device.initSequencer.initialize(this, initOrderNumber);
    while (running)
        loop();
}

void RenderThread::stop(void){
    running = false;
}

void RenderThread::join(void){
    thread.join();

    // re-enable gl context for main thread
    device.glContextMutex.getWindow().setActive(true);
}

void RenderThread::init(void){
    // enable depth test
    glEnable(GL_DEPTH_TEST);
    // accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glClearColor(1.0f, 0.055f, 0.48f, 1.0f);
}

void RenderThread::loop(void){
    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render
    {
        std::lock_guard<std::mutex> lock(rendererMapMutex);
        for(auto& pRendererPair : mpRenderers)
            pRendererPair.first->render();
    }

    // show the rendered stuff
    device.glContextMutex.getWindow().display();

    // lend the GL context if needed
    if(device.glContextMutex.getWaitingThreads()){
        device.glContextMutex.unlock();
        device.glContextMutex.lock();
    }
}
