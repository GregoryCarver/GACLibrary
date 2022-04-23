#pragma once
#include "Grid.h"
#include "Point.h"

class Graph
{
	std::vector<Vertex> vertices;
	glm::vec3 position;
	glm::vec3 rotation;
	std::vector<Point> points;
	glm::mat4 modelMatrix;
	float scale;
	unsigned int VAO;


public:
	Graph(float x = 0.0f, float y = 0.0f, float z = 0.0f, float scale = 1.0f);

	std::vector<Vertex> GetVertices();
	glm::vec3 GetPosition();
	glm::mat4 GetModelMatrix();

	void Transform(glm::mat4 transformationMatrix);
	void Rotate(float degrees, glm::vec3 axisOfRotation = glm::vec3(0.0f, 1.0f, 0.0f));

	void PlotPoint(glm::vec3 localPosition);
	void PlotFunction(unsigned int function, unsigned int pointCount, float offset = 0.0f);
};