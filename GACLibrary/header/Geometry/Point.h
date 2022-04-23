#pragma once
#include <vector>
#include "Vertex.h"

class Point
{
	glm::vec3 position;
	std::vector<Vertex> vertices;

public:
	Point(glm::vec3 position, float pointSize = 0.01f);

	std::vector<Vertex> GetVertices();
	glm::vec3 GetPosition();

	void Transform(glm::mat4 transformationMatrix);
};