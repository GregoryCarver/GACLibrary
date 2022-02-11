#include <glew.h>
#include <glfw3.h> 
#include <iostream>

#include "Shader.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"

int main(void)
{
    /********************************************* GLEW AND GLFW INITIALIZATION ***********************************************/
    GLFWwindow* window;

    /* Initialize the glfw library */
    if (!glfwInit())
    {
        std::cout << "Couldn't initialize GLFW!" << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Window of the GODS!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Couldn't initialize GLEW!" << std::endl;
        return -1;
    }
    /******************************************** GLEW AND GLFW INITIALIZATION END ********************************************/

    Shader shader = Shader("resources/shaders/SimpleVertexShader.vert", "resources/shaders/SimpleFragmentShader.frag");

    float vertices[] =
    {
        //positions             //colors
        0.5f,  0.5f, 0.0f,      0.0f, 0.0f, 0.5f,      //top right
        0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      //bottom right
       -0.5f, -0.5f, 0.0f,      0.0f, 0.5f, 0.0f,      //bottom left
       -0.5f,  0.5f, 0.0f,      0.5f, 0.0f, 0.0f       //top left
    };
    float vertices2[] =
    {
        //positions             //colors
        0.5f,  0.5f, 0.0f,      0.0f, 0.0f, 0.5f,      //top right
        0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      //bottom right
       -0.5f, -0.5f, 0.0f,      0.0f, 0.5f, 0.0f,      //bottom left
       -0.5f,  0.5f, 0.0f,      0.5f, 0.0f, 0.0f       //top left
    };

    unsigned int indices[]
    {
        0, 1, 3,    //first triangle
        1, 2, 3     //second triangle
    };

    VertexArray vertexArray;

    VertexBuffer vertexBuffer(sizeof(vertices), vertices);
    vertexArray.AddBuffer(vertexBuffer, 2);
    ElementBuffer elementBuffer(sizeof(indices), indices);

    shader.Use();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}