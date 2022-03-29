#include "Vertex.h"

Vertex::Vertex()
{
	x = y = z = r = 0.0f;
	g = 0.5f;
	b = 0.7f;
	a = 1.0f;
}

Vertex::Vertex(float x, float y, float z, float a) : r(0.0f), g(0.5f), b(0.7f)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->a = a;
}
