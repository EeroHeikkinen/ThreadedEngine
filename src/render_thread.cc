#include "render_thread.hh"
#include "device.hh"

#include <GL/GLEW.h>
#include <SFML/OpenGL.hpp>
#include <iostream> //TEMP


RenderThread::RenderThread(Device* pDevice, unsigned int initOrderNumber) :
    running(true),
    initOrderNumber(initOrderNumber),
    windowInitialized(false)
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
        windowInitialized = true;

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
        thread = std::thread(&RenderThread::launch, this);
    }

RenderThread::~RenderThread(void){
    if (running){
        running = false;
        thread.join();
    }
    delete pWindow;
}

void RenderThread::launch(void){
    // render thread begins here
    DEVICE.initSequencer.initialize(this, initOrderNumber);
    while (running)
        loop();
}

void RenderThread::stop(void){
    running = false;
}

void RenderThread::join(void){
    thread.join();
}

void RenderThread::init(void){
    // set GL context active for render thread
    glContextMutex.gainOwnership();
    while (!pWindow->setActive(true))
        sf::sleep(sf::milliseconds(5));

    // enable depth test
    glEnable(GL_DEPTH_TEST);
    // accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
}

void RenderThread::loop(void){
    // clear the buffers
    glClearColor(1.0f, 0.35f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        while(!pWindow->setActive(false)) //get ridda dis spinlock!
            sf::sleep(sf::milliseconds(5));
        //wait for other threads to do their work
        glContextMutex.dispatchInterrupts();

        while(!pWindow->setActive(true)) //und dis too!
            sf::sleep(sf::milliseconds(5));
    }

    // delay
    sf::sleep(sf::milliseconds(10));
    /*
    TODO
    Improve the delay
    */
}

sf::Window* RenderThread::getWindowPtr(void){
    return pWindow;
}

bool RenderThread::isWindowInitialized(void){
    return windowInitialized;
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

/*void RenderThread::addRenderers(tbb::concurrent_vector<Renderer*>& vpRenderers_){
    for(auto pRenderer : vpRenderers_)
        vpRenderers.push_back(pRenderer);
}*/
