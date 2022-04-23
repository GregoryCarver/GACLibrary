#include <gtc/matrix_transform.hpp>
#include "Geometry/Graph.h"
#include "Geometry/DoubleArrow.h"
#include <iostream>

//Graph::Graph(float x, float y, float z, float scale)
//{
//    this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
//    this->scale = scale;
//    position = glm::vec3(x, y, z);
//    glm::mat4 mod = glm::mat4(1.0f);
//    glm::mat4 translation = glm::translate(mod, glm::vec3(x, y, z));
//    mod = glm::rotate(translation, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//    DoubleArrow xAxis = DoubleArrow(Vertex(0.0f, 0.5f, 0.0f), Vertex(0.0f, -0.5, 0.0f));
//    xAxis.Transform(mod);
//    DoubleArrow yAxis = DoubleArrow(Vertex(0.0f, 0.5f, 0.0f), Vertex(0.0f, -0.5, 0.0f));
//    yAxis.Transform(translation);
//    mod = glm::rotate(translation, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    mod = glm::rotate(mod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//    DoubleArrow zAxis = DoubleArrow(Vertex(0.0f, 0.5f, 0.0f), Vertex(0.0f, -0.5, 0.0f));
//    zAxis.Transform(mod);
//    std::vector<Vertex> xAxisVerts = xAxis.GetVertices();
//    std::vector<Vertex> yAxisVerts = yAxis.GetVertices();
//    std::vector<Vertex> zAxisVerts = zAxis.GetVertices();
//
//    vertices.insert(vertices.end(), xAxisVerts.begin(), xAxisVerts.end());
//    vertices.insert(vertices.end(), yAxisVerts.begin(), yAxisVerts.end());
//    vertices.insert(vertices.end(), zAxisVerts.begin(), zAxisVerts.end());
//}

Graph::Graph(float x, float y, float z, float scale)
{
    this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->scale = scale;
    this->position = glm::vec3(x, y, z);
    this->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 rotation = glm::rotate(identity, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    DoubleArrow xAxis = DoubleArrow(Vertex(0.0f, 0.5f, 0.0f), Vertex(0.0f, -0.5, 0.0f));
    xAxis.Transform(rotation);

    DoubleArrow yAxis = DoubleArrow(Vertex(0.0f, 0.5f, 0.0f), Vertex(0.0f, -0.5, 0.0f));

    rotation = glm::rotate(identity, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotation = glm::rotate(rotation, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    DoubleArrow zAxis = DoubleArrow(Vertex(0.0f, 0.5f, 0.0f), Vertex(0.0f, -0.5, 0.0f));
    zAxis.Transform(rotation);

    std::vector<Vertex> xAxisVerts = xAxis.GetVertices();
    std::vector<Vertex> yAxisVerts = yAxis.GetVertices();
    std::vector<Vertex> zAxisVerts = zAxis.GetVertices();

    vertices.insert(vertices.end(), xAxisVerts.begin(), xAxisVerts.end());
    vertices.insert(vertices.end(), yAxisVerts.begin(), yAxisVerts.end());
    vertices.insert(vertices.end(), zAxisVerts.begin(), zAxisVerts.end());
}

std::vector<Vertex> Graph::GetVertices()
{
    std::vector<Vertex> allVerts = vertices;
    for (Point& point : points)
    {
        std::vector<Vertex> pointVerts = point.GetVertices();
        allVerts.insert(allVerts.end(), pointVerts.begin(), pointVerts.end());
    }

    return allVerts;
}

glm::vec3 Graph::GetPosition()
{
    return position;
}

glm::mat4 Graph::GetModelMatrix()
{
    return modelMatrix;
}

void Graph::Transform(glm::mat4 transformationMatrix)
{
    for (Vertex& vertex : vertices)
    {
        vertex.Transform(transformationMatrix);
    }
}

void Graph::Rotate(float degrees, glm::vec3 axisOfRotation)
{
    this->rotation = axisOfRotation * degrees;
    glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position);
    transformation = glm::rotate(transformation, glm::radians(degrees), axisOfRotation);
    transformation = glm::translate(transformation, -position);
    this->modelMatrix = transformation;

    /*for (Vertex& vertex : vertices)
    {
        vertex.Transform(transformation);
    }
    for (Point& point : points)
    {
        point.Transform(transformation);
    }*/
}

void Graph::PlotPoint(glm::vec3 localPosition)
{
    if (localPosition.x < scale && localPosition.y < scale && localPosition.z < scale)
    {
        //MAY BE ABLE TO JUST TAKE PERCENTAGES OF THE ROTATION OF GRAPH TO CONFIGURE POINT ROTATION
        //SECOND THOUGHT, am I just applying the graph transformation to the points, seems like that may lead to a solution
        Point newPoint = Point(localPosition / (this->scale * 2));

        /*glm::mat4 transformation = glm::translate(glm::mat4(1.0f), this->position);
        transformation = glm::rotate(transformation, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transformation = glm::translate(transformation, -(this->position));
        newPoint.Transform(transformation);*/
        
        points.push_back(newPoint);
    }
}
    

void Graph::PlotFunction(unsigned int function, unsigned int pointCount, float offset)
{
    points.clear();
    for (unsigned int i = 0; i <= pointCount; i++)
    {
        switch (function)
        {
            case 0:
            {
                PlotPoint(glm::vec3(cos(5.0f * ((float)i / (float)pointCount) + offset), ((float)i / (float)pointCount), 0.0f));
                break;
            }
            case 1:
                break;
            case 2:
                break;
        }
    }
}