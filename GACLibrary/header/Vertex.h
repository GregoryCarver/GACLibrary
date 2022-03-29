#pragma once

#include <vector>

struct Vertex
{
	float x, y, z, r, g, b, a;

	Vertex();
	Vertex(float x, float y, float z, float a = 1.0f);
};
