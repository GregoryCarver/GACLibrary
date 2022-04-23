#pragma once
#include "Line.h"

//Class used to create grid of lines, can be used in things like signifying the x-y plane, or any case a grid may be useful
class Grid
{
	unsigned int VAO;
	std::vector<Line> lines;

public:
	Grid(unsigned int width = 8, unsigned int length = 8, float transparency = 0.5f);

	std::vector<Vertex> GetVertices();
	unsigned int GetVAO();
	void SetVAO(unsigned int VAOID);
	void Transform(glm::mat4 transformationMatrix);
};