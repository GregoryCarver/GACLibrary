#pragma once
#include "Line.h"

class Grid
{

	std::vector<Line> lines;

public:
	Grid(unsigned int width = 8, unsigned int length = 8, float transparency = 0.1f);

	std::vector<Vertex> GetVertices();
};