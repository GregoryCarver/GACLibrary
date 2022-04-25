#pragma once
#include "Grid.h"
#include "Point.h"

class Graph
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 size;
	float scale;
	glm::mat4 modelMatrix;
	std::vector<Vertex> vertices;
	std::vector<Vertex> points;
	unsigned int VAO;


public:
	Graph(float x = 0.0f, float y = 0.0f, float z = 0.0f, float scale = 1.0f);

	std::vector<Vertex> GetVertices();
	std::vector<Vertex> GetGraphVerts();
	std::vector<Vertex> GetPointVerts();
	glm::vec3 GetPosition();
	glm::mat4 GetModelMatrix();

	void Transform(glm::mat4 transformationMatrix);
	void Rotate(float degrees, glm::vec3 axisOfRotation = glm::vec3(0.0f, 1.0f, 0.0f));

	void PlotPoint(Vertex localPosition);
	void PlotFunction(unsigned int function, int pointCount, float offset = 0.0f);
};