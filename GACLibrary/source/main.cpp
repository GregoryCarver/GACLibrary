/*******************************************************************************************************************************************************
* Gregory Carver
* Last Edited: 16 Apr 2022
* Things to do/last done: 
*   - LAST: added points, and plot points to graphs
*   - TODO: start working on Graph object(change of coordinates and scaling) PARTIALLY DONE
*   - TODO: finish plot function for graphs
*   - IDEA: maybe having two sets of vertices for an object, one set for the vertices that are almost guaranteed to not change, and another set for
*           vertices that are almost guaranteed to change. Also, the headers of more primitive types may be able to go in source files instead of
*           header files then.
*   - IDEA: maybe add stuff like .rotate and .translate to the individual objects
*   - IDEA: maybe go back and use inheritance, as a lot of the "primitives" I'm developing are containing the same functions
*   - IDEA: should things like grid really be composed of things like lines, does it save work or make sense that way? If not, it may be easier to just
*           build the vertices of the object, such as grid, directly in the constructor, instead of using lines.
*
*   --- AFTER THIS PROJECT: - going to need to refactor, for example inheritance can clean things up quite a bit. REFACTOR REFACTOR REFACTOR!!!
                            - added some ugly code in point to configure point rotation and function plotting, clean that up asap before I forget what's what
                            - transformation of the graph
*******************************************************************************************************************************************************/

#include <glew.h>
#include <glfw3.h> 
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <map>

#include "Shader.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Camera.h"

//INCLUDED WHILE TESTING
//#include "Vertex.h"
//#include "Geometry/Line.h"
//#include "Geometry/Grid.h"
#include "Geometry/Graph.h"
#include "Geometry/DoubleArrow.h"
#include "Geometry/Point.h"

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
    Shader instanceShader = Shader("resources/shaders/CameraInstanceShader.vert", "resources/shaders/SimpleFragmentShader.frag");

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

    //Test objects
    Grid worldGrid = Grid(1000, 1000, 0.25f);
    std::vector<Graph> testGraphs;
    /*testGraphs.push_back(Graph(1.0f, 1.0f, -1.0f, 1.0f));
    testGraphs.push_back(Graph(2.0f, 1.0f, -0.0f, 1.0f));
    testGraphs.push_back(Graph(0.0f, 0.0f, -1.0f, 1.0f))*/;
    float scale = 1.0f;
    for (int i = -10; i < 11; i += 2)
    {
        for (int j = 0; j < 21; j += 2)
        {
            testGraphs.push_back(Graph((float)i, (float)j, 5.0f, scale));
        }
    }

    testGraphs.push_back(Graph(0.0f, 0.0f, -1.0f, 1.0f));

    //Test objects transformations
    glm::mat4 mod = glm::mat4(1.0f);
    mod = glm::translate(mod, glm::vec3(0.0f, -1.0f, 0.0f));
    worldGrid.Transform(mod);
    //testGraphs[0].Rotate(45.0f);

    //testGraph.PlotFunction(0, 50);

    ////Adding verts to same vector, so all can be drawn at once
    std::vector<Vertex> gridVerts = worldGrid.GetVertices();
    std::vector<Vertex> graphVerts = testGraphs[0].GetVertices();
    //std::vector<Vertex> graphVerts = testGraph.GetVertices();

    //gridVerts.insert(gridVerts.end(), graphVerts.begin(), graphVerts.end());
    std::map<unsigned int, VertexArray> vertexArrays;

    VertexArray gridVertexArray(gridVerts);
    vertexArrays[gridVertexArray.GetVAOID()] = gridVertexArray;
    worldGrid.SetVAO(gridVertexArray.GetVAOID());
    vertexArrays[worldGrid.GetVAO()].AddAttribPointer(0, sizeof(gridVerts[0].position), sizeof(Vertex), 0);
    vertexArrays[worldGrid.GetVAO()].AddAttribPointer(1, sizeof(gridVerts[0].color), sizeof(Vertex), sizeof(gridVerts[0].position));

    //Was testing out a dictionary method both ^ above, and with graph vertices v below, not sure if it could be beneficial yet
    VertexArray graphVertexArray(graphVerts);
    vertexArrays[graphVertexArray.GetVAOID()] = graphVertexArray;
    graphVertexArray.AddAttribPointer(0, sizeof(graphVerts[0].position), sizeof(Vertex), 0);
    graphVertexArray.AddAttribPointer(1, sizeof(graphVerts[0].color), sizeof(Vertex), sizeof(graphVerts[0].position));

    /*unsigned int modelMatricesBuffer;
    glGenBuffers(1, &modelMatricesBuffer);*/
    glm::mat4* modelMatrices = new glm::mat4[testGraphs.size()];
    for (unsigned int i = 0; i < testGraphs.size(); i++)
    {
        modelMatrices[i] = testGraphs[i].GetModelMatrix();
    }

    //graphVertexArray.AddBuffer(modelMatrices, 1);

    /*graphVertexArray.AddAttribPointer(2, sizeof(glm::vec4), sizeof(glm::mat4), 0, 1);
    graphVertexArray.AddAttribPointer(3, sizeof(glm::vec4), sizeof(glm::mat4), sizeof(glm::vec4), 1);
    graphVertexArray.AddAttribPointer(4, sizeof(glm::vec4), sizeof(glm::mat4), sizeof(glm::vec4) * 2, 1);
    graphVertexArray.AddAttribPointer(5, sizeof(glm::vec4), sizeof(glm::mat4), sizeof(glm::vec4) * 3, 1);*/

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, testGraphs.size() * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 2));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 3));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glBindVertexArray(0);

    //VertexBuffer vertexBuffer(sizeof(vertices), vertices);
    //vertexArray.AddBuffer(vertexBuffer, 2);
    //ElementBuffer elementBuffer(sizeof(indices), indices);

    //VertexArray vertexArray2;

    //VertexBuffer vertexBuffer2(sizeof(vertices2), vertices2);
    //vertexArray2.AddBuffer(vertexBuffer2, 2);

    //VertexArray vertexArray3;
    //vertexArray3.AddBuffer(gridVerts);
    /*VertexBuffer vertexBuffer3(gridVerts);
    vertexArray3.AddBuffer(vertexBuffer3);*/
    //return 0;

    /******************************************** EXAMPLE       GEOMETRY       END ********************************************/
    /*                                                                                                                        */
    /**************************************************************************************************************************/

    //Enable transparency to enable transparency in lines
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    float t = 0.0f;
    std::vector<float> ts;
    for (int i = 0; i < testGraphs.size(); i++)
    {
        ts.push_back((float)(rand() % 7));
    }
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //Process Input
        ProcessInput(window);

        /* Render here */
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        //Pass the projection matrix to shader ( in this case could change every frame )
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "projection"), 1, GL_FALSE, &projection[0][0]);
        //Camera view transformation.
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "view"), 1, GL_FALSE, &view[0][0]);
        //Camera view transformation.
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "model"), 1, GL_FALSE, &model[0][0]);

        gridVertexArray.Bind();
        glDrawArrays(GL_LINES, 0, gridVerts.size());

        instanceShader.Use();
        glUniformMatrix4fv(glGetUniformLocation(instanceShader.GetID(), "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(instanceShader.GetID(), "view"), 1, GL_FALSE, &view[0][0]);
        graphVertexArray.Bind();
        for (int i = 0; i < testGraphs.size(); i++)
        {
            testGraphs[i].PlotFunction(0, 20, ts[i]);
            /**************************TESTING INSTANCES*****************************/
            std::vector<Vertex> graphVerts = testGraphs[i].GetVertices();
            graphVertexArray.UpdateBuffer(graphVerts, 0);
            
            //graphVertexArray.AddAttribPointer(0, sizeof(graphVerts[0].position), sizeof(Vertex), 0);
            //graphVertexArray.AddAttribPointer(1, sizeof(graphVerts[0].color), sizeof(Vertex), sizeof(graphVerts[0].position));

            /*glm::mat4* modelMatrices = new glm::mat4[testGraphs.size()];
            for (unsigned int i = 0; i < testGraphs.size(); i++)
            {
                modelMatrices[i] = testGraphs[i].GetModelMatrix();
            }

            unsigned int buffer;
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, testGraphs.size() * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0));
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 2));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 3));

            glVertexAttribDivisor(2, 1);
            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);*/
            /**************************TESTING INSTANCES END*****************************/

            glDrawArraysInstanced(GL_LINES, 0, testGraphs[i].GetVertices().size(), testGraphs.size());
            //glDrawArrays(GL_LINES, 0, graphVerts.size());
        }
        /******************************* TESTING ANIMATED GRAPHS ***************************************/
        //std::vector<Vertex> gridVerts = worldGrid.GetVertices();

        //for (Graph& graph : testGraphs)
        //{
        //    graph.PlotFunction(0, 50, t);
        //    //Adding verts to same vector, so all can be drawn at once
        //    std::vector<Vertex> graphVerts = graph.GetVertices();

        //    gridVerts.insert(gridVerts.end(), graphVerts.begin(), graphVerts.end());
        //}

        for (float& t : ts)
        {
            t = t + 0.1f;
            if (t > 6.28f) { t = 0.0f; }
        }
        

        //VertexArray vertexArray;

        //VertexBuffer vertexBuffer(sizeof(vertices), vertices);
        //vertexArray.AddBuffer(vertexBuffer, 2);
        //ElementBuffer elementBuffer(sizeof(indices), indices);

        //VertexArray vertexArray2;

        //VertexBuffer vertexBuffer2(sizeof(vertices2), vertices2);
        //vertexArray2.AddBuffer(vertexBuffer2, 2);

        //VertexArray vertexArray3;
        //vertexArray3.AddBuffer(gridVerts);

        /*****************************END TESTING ANIMATED GRAPHS *****************************************/

        /*vertexArray.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vertexArray2.Bind();
        glDrawArrays(GL_LINES, 0, 4);*/
        //vertexArray3.Bind();
        //glDrawArraysInstanced(GL_LINES, 0, )

        glBindVertexArray(0);

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