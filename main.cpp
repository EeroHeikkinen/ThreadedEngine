#include "src/shader.hpp"

#include <SFML/Window.hpp>
#include <GL/GLEW.h>
#include <SFML/OpenGL.hpp>
#include <iostream> //temp


#define GLEW_STATIC


using namespace std; //temp


int main()
{
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

    // load resources, initialize the OpenGL states, ...

    // initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "GLEW initialization failed." << endl;
        return 1;
    }

    // some vertex data
    const GLuint nVertices = 3;
    const GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };

    const GLuint nIndices = 3;
    const GLushort indices[] = {
        0, 1, 2
    };

    // buffers and VAO
    GLuint VBO, IBO, VAO;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    glGenVertexArrays(1, &VAO);

    // filling the buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 4*3*nVertices, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2*nIndices, indices, GL_STATIC_DRAW);

    // configuring the vertex array object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    // VAO done, unbinding
    glBindVertexArray(0);

    // shader program
    Shader myShader;
    ShaderObject* VSO = new ShaderObject(GL_VERTEX_SHADER, "shaders/VS_basic.glsl");
    ShaderObject* FSO = new ShaderObject(GL_FRAGMENT_SHADER, "shaders/FS_basic.glsl");
    myShader.addShaderObject(VSO); //vertex shader
    myShader.addShaderObject(FSO); //fragment shader
    myShader.link();


    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
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

        // draw...
        glBindVertexArray(VAO);
        myShader.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (GLvoid*)0);
        glBindVertexArray(0);

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);

    return 0;
}
