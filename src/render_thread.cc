#include "render_thread.hh"
#include "device.hh"

#include <GL/GLEW.h>
#include <SFML/OpenGL.hpp>
#include <iostream> //TEMP


RenderThread::RenderThread(Device& device) :
    device(device),
    running(true),
    windowInitialized(false),
    deactivatingContext(false) {

    // window settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    // create the window
    pWindow = new sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    pWindow->setVerticalSyncEnabled(true);
    windowInitialized = true;

    // initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
        std::cout << "GLEW initialization failed." << std::endl;//TEMP
    else
        device.setGlewInitialized(true);
    /*
    TODO
    An exception needs to be thrown in case of GLEW initialization failure.
    */

    // disable GL context for main thread
    while (!pWindow->setActive(false)) {
        sf::sleep(sf::milliseconds(5));
    }

    // launch render thread
    thread = std::thread(&RenderThread::launch, this);
}

RenderThread::~RenderThread(void) {
    if (running) {
        running = false;
        thread.join();
    }

    delete pWindow;
}

void RenderThread::launch(void) {
    // render thread begins here
    init();

    while (running)
        loop();
}

void RenderThread::stop(void) {
    running = false;
}

void RenderThread::join(void) {
    thread.join();
}

void RenderThread::init(void) {
    // set GL context active for render thread
    glContextMutex.lock();
    while (!pWindow->setActive(true)) {
        sf::sleep(sf::milliseconds(5));
    }
}

void RenderThread::loop(void) {
    // clear the buffers
    glClearColor(0.0f, 1.0f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render
    for (auto it = vpRenderComponents.begin(); it != vpRenderComponents.end(); it++) {
        (*it)->render();
    }

    // show the rendered stuff
    pWindow->display();

    // check if another thread(resource) wants to deactivate GL context
    if (deactivatingContext) {
        while (!pWindow->setActive(false)) {
            sf::sleep(sf::milliseconds(5));
        }
        glContextMutex.unlock(); // deactivated succesfully
        deactivatingContext = false;

        // another thread does its thing

        glContextMutex.lock();
        while (!pWindow->setActive(true)) {
            sf::sleep(sf::milliseconds(5));
        }
    }

    // delay
    sf::sleep(sf::milliseconds(10));
    /*
    TODO
    Improve the delay
    */
}

sf::Window* RenderThread::getWindowPtr(void) {
    return pWindow;
}

bool RenderThread::isWindowInitialized(void) {
    return windowInitialized;
}

void RenderThread::detachContext(void) {
    deactivatingContext = true;
    // once deactivated successfully, glContextMutex lock is gained by another thread:
    glContextMutex.lock();
    while (!pWindow->setActive(true)) {
        sf::sleep(sf::milliseconds(5));
    }
}

void RenderThread::attachContext(void) {
    while (!pWindow->setActive(false)) {
        sf::sleep(sf::milliseconds(5));
    }
    glContextMutex.unlock();
}

void RenderThread::addRenderComponent(RenderComponent* pRenderComponent) {
    vpRenderComponents.push_back(pRenderComponent);
}

void RenderThread::deleteRenderComponent(RenderComponent* pRenderComponent) {
    for (auto it = vpRenderComponents.begin(); it != vpRenderComponents.end(); it++) {
        if (*it == pRenderComponent) {
            vpRenderComponents.erase(it);
            return;
        }
    }
}
