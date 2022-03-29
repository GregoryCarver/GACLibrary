#include <glew.h>
#include <glfw3.h> 
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Camera.h"

//INCLUDED WHILE TESTING
#include "Vertex.h"
#include "Geometry/Line.h"
#include "Geometry/Grid.h"

//Global screen settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Global timing variables. Timing scheme used from an old project
float deltaTime = 0.0f;         //Time difference of current frame and last frame.
float lastTime = 0.0f;          //Keeps track of the time of the last frame. Used to calculate deltaTime.
double previousFPSTime = glfwGetTime();
int frameCount = 0;

//Global input vairables
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;             //Last x coordinate of the camera.
float lastY = SCR_HEIGHT / 2.0f;            //Last y coordinate of the camera.
bool firstMouse = true;                     //Makes sure the screen doesn't snap when entering the screen with the mouse.

void ProcessInput(GLFWwindow* window);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);

int main(void)
{
    /******************************************** GLEW AND GLFW INITIALIZATION ************************************************/
    /*                                                                                                                        */
    /**************************************************************************************************************************/
    GLFWwindow* window;
    

    /* Initialize the glfw library */
    if (!glfwInit())
    {
        std::cout << "Couldn't initialize GLFW!" << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Window of the GODS!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, MouseCallback);

    //Tells GLFW to capture our mouse.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Initialize GLEW */
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Couldn't initialize GLEW!" << std::endl;
        return -1;
    }
    /******************************************** GLEW AND GLFW INITIALIZATION END ********************************************/
    /*                                                                                                                        */
    /**************************************************************************************************************************/

    Shader shader = Shader("resources/shaders/CameraShader.vert", "resources/shaders/SimpleFragmentShader.frag");

    /******************************************** EXAMPLE       GEOMETRY       START ******************************************/
    /*                                                                                                                        */
    /**************************************************************************************************************************/
    float vertices[] =
    {
        //positions             //colors
        0.5f,  0.5f, 0.1f,      0.7f, 0.0f, 0.0f,      //top right
        0.5f, -0.5f, 0.1f,      0.7f, 0.0f, 0.0f,      //bottom right
       -0.5f, -0.5f, 0.1f,      0.7f, 0.0f, 0.0f,      //bottom left
       -0.5f,  0.5f, 0.1f,      0.7f, 0.0f, 0.0f       //top left
    };
    float vertices2[] =
    {
        //positions             //colors
        0.5f,  0.5f,  0.0f,      0.0f, 0.5f, 0.7f,      //top right
        0.5f, -0.5f,  0.0f,      0.0f, 0.5f, 0.7f,      //bottom right
       -0.5f, -0.5f,  0.0f,      0.0f, 0.5f, 0.7f,      //bottom left
       -0.5f,  1.0f, -0.2f,      0.0f, 0.5f, 0.7f       //top left
    };

    unsigned int indices[]
    {
        0, 1, 3,    //first triangle
        1, 2, 3     //second triangle
    };

    //Line line = Line(Vertex(0.0f, 0.0f, -1.0f), Vertex(0.0f, 0.0f, 1.0f));
    Grid grid = Grid();
    std::vector<Vertex> gridVerts = grid.GetVertices();

    VertexArray vertexArray;

    VertexBuffer vertexBuffer(sizeof(vertices), vertices);
    vertexArray.AddBuffer(vertexBuffer, 2);
    ElementBuffer elementBuffer(sizeof(indices), indices);

    VertexArray vertexArray2;

    VertexBuffer vertexBuffer2(sizeof(vertices2), vertices2);
    vertexArray2.AddBuffer(vertexBuffer2, 2);

    VertexArray vertexArray3;
    vertexArray3.AddBuffer(gridVerts);

    /*VertexBuffer vertexBuffer3(gridVerts);
    vertexArray3.AddBuffer(vertexBuffer3);*/

    /******************************************** EXAMPLE       GEOMETRY       END ********************************************/
    /*                                                                                                                        */
    /**************************************************************************************************************************/

    shader.Use();

    //Enable transparency to enable transparency in lines
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //Process Input
        ProcessInput(window);

        /* Render here */
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Pass the projection matrix to shader ( in this case could change every frame )
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "projection"), 1, GL_FALSE, &projection[0][0]);

        //Camera view transformation.
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "view"), 1, GL_FALSE, &view[0][0]);

        //Camera view transformation.
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "model"), 1, GL_FALSE, &model[0][0]);

        /*vertexArray.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vertexArray2.Bind();
        glDrawArrays(GL_LINES, 0, 4);*/
        vertexArray3.Bind();
        glDrawArrays(GL_LINES, 0, gridVerts.size());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

//All input was modified and used from and old project, most of it was modified from learnopengl.com
void ProcessInput(GLFWwindow* window)
{
    //Get the time variables and display fps
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    frameCount++;
    if (currentTime - previousFPSTime >= 1.0f)
    {
        std::cout << "FPS: " << frameCount << "\r";
        frameCount = 0;
        previousFPSTime = currentTime;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos; //y-coordinates go from bottom to top.

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}