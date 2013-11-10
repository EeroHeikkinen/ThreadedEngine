#include "render_thread.hh"
#include "device.hh"

#include <GL/GLEW.h>
#include <SFML/OpenGL.hpp>
#include <iostream> //temp


RenderThread::RenderThread(Device& device) :
    device(device),
    running(true) {
    thread = std::thread(&RenderThread::launch, this);
}

RenderThread::~RenderThread(void) {
    if (running) {
        running = false;
        thread.join();
    }
}

void RenderThread::launch(void) {
    //New thread begins here
    init();

    // window settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    // initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
        std::cout << "GLEW initialization failed." << std::endl;
    /*
    TODO
    An exception needs to be thrown in case of GLEW initialization failure.
    */

    while (running) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                device.stop();
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClearColor(0.0f, 1.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.display();
    }
}

void RenderThread::stop(void) {
    running = false;
}

void RenderThread::join(void) {
    thread.join();
}

void RenderThread::init(void) {
    std::cout << "Helloes from RenderThread!" << std::endl;//temp


}

void RenderThread::loop(void) {

}

sf::Window& RenderThread::getWindow(void) {
    return window;
}
