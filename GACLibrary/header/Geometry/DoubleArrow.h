#pragma once
#include "Line.h"

class DoubleArrow
{
	std::vector<Vertex> vertices;

public:
	DoubleArrow(Vertex start, Vertex end);

	std::vector<Vertex> GetVertices();
	void Transform(glm::mat4 transformationMatrix);
};