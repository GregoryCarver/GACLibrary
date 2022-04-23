#pragma once

#include "Vertex.h"

enum Color
{
	RED,
	GREEN,
	BLUE,
	BLACK,
	WHITE,
	CLEAR
};

class Line
{
	Vertex start, end;

public:
	Line(Vertex start = Vertex(0.0f, 0.0f, 0.0f), Vertex end = Vertex(1.0f, 0.0f, 0.0f));
	Line(Color color, Vertex start = Vertex(0.0f, 0.0f, 0.0f), Vertex end = Vertex(1.0f, 0.0f, 0.0f));
	Line(float startX, float startY, float startZ, float endX, float endY, float endZ, float transparency);
	//Line(Vertex start = Vertex(0.0f, 0.0f, 0.0f), Vertex end = Vertex(1.0f, 0.0f, 0.0f), float r, float g, float b, float a);
	
	Vertex GetStart();
	Vertex GetEnd();
	std::vector<Vertex> GetVertices();
	void Transform(glm::mat4);
};