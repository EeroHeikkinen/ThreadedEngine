#include "render_thread.hh"
#include "device.hh"

#include <GL/GLEW.h>
#include <SFML/OpenGL.hpp>
#include <iostream>


RenderThread::RenderThread(Device* pDevice, unsigned int initOrderNumber) :
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
        pWindow = new sf::Window(sf::VideoMode(1280, 960), "OpenGL", sf::Style::Default, settings);
        pWindow->setVerticalSyncEnabled(true);

        // initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK)
            std::cout << "GLEW initialization failed." << std::endl;//TEMP

        /*
        TODO
        An exception needs to be thrown in case of GLEW initialization failure.
        */

        // disable GL context for main thread
        while (!pWindow->setActive(false))
            sf::sleep(sf::milliseconds(5));

        // launch render thread
        thread = std::thread(&RenderThread::launch, this, initOrderNumber);
    }

RenderThread::~RenderThread(void){
    if (running){
        running = false;
        thread.join();
    }
    delete pWindow;
}

void RenderThread::launch(unsigned int initOrderNumber){
    glContextMutex.gainOwnership();

    while (!pWindow->setActive(true))
        sf::sleep(sf::milliseconds(5));

    DEVICE.initSequencer.initialize(this, initOrderNumber);
    while (running)
        loop();

    while (!pWindow->setActive(false))
        sf::sleep(sf::milliseconds(5));
}

void RenderThread::stop(void){
    running = false;
}

void RenderThread::join(void){
    thread.join();
}

void RenderThread::init(void){
    // enable depth test
    glEnable(GL_DEPTH_TEST);
    // accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glClearColor(1.0f, 0.055f, 0.48f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderThread::loop(void){
    // clear the buffers
    //glClearColor(1.0f, 0.055f, 0.48f, 1.0f);
    static int asd = 0;
    ++asd;
    if (asd > 30) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        asd = 0;
    }

    // render
    {
        std::lock_guard<std::mutex> lock(rendererMapMutex);
        for(auto& pRendererPair : mpRenderers)
            pRendererPair.first->render();
    }

    // show the rendered stuff
    pWindow->display();

    // check if other threads want to borrow the GL context
    if(glContextMutex.checkInterrupts()){
        while(!pWindow->setActive(false))
            sf::sleep(sf::milliseconds(5));
        //wait for other threads to do their work
        glContextMutex.dispatchInterrupts();

        while(!pWindow->setActive(true))
            sf::sleep(sf::milliseconds(5));
    }

    // delay
    sf::sleep(sf::milliseconds(5));
    /*
    TODO
    Improve the delay
    */
}

sf::Window* RenderThread::getWindowPtr(void){
    return pWindow;
}

//a thread can call this to borrow the glContext
void RenderThread::detachContext(void){
    glContextMutex.lock();

    while (!pWindow->setActive(true)) //omg dees spinlox!
        sf::sleep(sf::milliseconds(5));
}

//the same thread that detached the context shall call this function as well
void RenderThread::attachContext(void){
    while (!pWindow->setActive(false)) //even moar of 'em basterdz!
        sf::sleep(sf::milliseconds(5));

    glContextMutex.unlock();
}
