#include <gtc/matrix_transform.hpp>
#include "Geometry/Graph.h"
#include "Geometry/DoubleArrow.h"
#include <iostream>

Graph::Graph(float x, float y, float z, float scale)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->size = glm::vec3(1.0f, 1.0f, 1.0f);
    this->scale = scale;
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
    allVerts.insert(allVerts.end(), points.begin(), points.end());

    return allVerts;
}

std::vector<Vertex> Graph::GetGraphVerts()
{
    return vertices;
}

std::vector<Vertex> Graph::GetPointVerts()
{
    return points;
}

glm::vec3 Graph::GetPosition()
{
    return position;
}

glm::mat4 Graph::GetModelMatrix()
{
    //return modelMatrix;
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), this->position);
    glm::mat4 xRotation = glm::rotate(translation, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 yRotation = glm::rotate(xRotation, this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 zRotation = glm::rotate(yRotation, this->rotation.z, glm::vec3(1.0f, 0.0f, 1.0f));
    glm::mat4 scale = glm::scale(zRotation, size);
    return scale;
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

void Graph::PlotPoint(Vertex localPosition)
{
    //if (localPosition.GetX() < scale && localPosition.GetY() < scale && localPosition.GetZ() < scale)
    //{
        //Point newPoint = Point(localPosition / (this->scale * 2));        
        //points.push_back(newPoint);
        points.push_back(localPosition);
    //}
}
    

void Graph::PlotFunction(unsigned int function, int pointCount, float offset)
{
    points.clear();
    
    switch (function)
    {
        case 0:
        {
            for (unsigned int i = 0; i <= pointCount; i++)
            {
                PlotPoint(Vertex(cos(5.0f * ((float)i / (float)pointCount) + offset), ((float)i / (float)pointCount), sin(5.0f * ((float)i / (float)pointCount) + offset)));
            }
            break;
        }
        case 1:
            for (int x = -pointCount * 5 / 2.0f; x < pointCount * 5 / 2; x++)
            {
                for(int y = -pointCount * 5 / 2.0f; y < pointCount * 5 / 2; y++)
                {
                    float newX = (float)x / (pointCount);
                    float newY = (float)y / (pointCount);
                    PlotPoint(Vertex(newX / 10.0f, newY / 10.0f, sin(newX * newX + newY * newY) / 10.0f));
                }
            }
            break;
        case 2:
            for (int x = -pointCount * 5 / 2.0f; x < pointCount * 5 / 2; x++)
            {
                for (int y = -pointCount * 5 / 2.0f; y < pointCount * 5 / 2; y++)
                {
                    float newX = (float)x / (pointCount);
                    float newY = (float)y / (pointCount);
                    PlotPoint(Vertex(newX / 10.0f, newY / 10.0f, sin(newX *5) * cos(5 * newY) / 10.0f));
                }
            }
            break;
    }
}