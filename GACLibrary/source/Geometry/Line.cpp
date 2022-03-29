#include "Geometry/Line.h"

//Line::Line()
//{
//	start = Vertex(-0.5f, 0.0f, 0.0f);
//	end	= Vertex( 0.5f, 0.0f, 0.0f);
//}

Line::Line(Vertex start, Vertex end)
{
	this->start = start;
	this->end = end;
}

Line::Line(Color color, Vertex start, Vertex end)
{
	this->start = start;
	this->end = end;

	switch (color)
	{
	case RED:
		start.r = end.r = 1.0f;
		start.g = start.b = end.g = end.b = 0.0f;
		break;
	case GREEN:
		start.g = end.g = 1.0f;
		start.r = start.b = end.r = end.b = 0.0f;
		break;
	case BLUE:
		start.b = end.b = 1.0f;
		start.r = start.g = end.r = end.g = 0.0f;
		break;
	case BLACK:
		start.r = start.g = start.b = end.r = end.g = end.b = 0.0f;
		break;
	case WHITE:
		start.r = start.g = start.b = end.r = end.g = end.b = 1.0f;
		break;
	case CLEAR:
		start.a = end.a = 0.0f;
		break;
	default:
		break;
	}
}

Line::Line(float startX, float startY, float startZ, float endX, float endY, float endZ, float transparency)
{
	start = Vertex(startX, startY, startZ, transparency);
	end = Vertex(endX, endY, endZ, transparency);
}

Vertex Line::GetStart()
{
	return start;
}

Vertex Line::GetEnd()
{
	return end;
}

std::vector<Vertex> Line::GetVertices()
{
	return std::vector<Vertex>{start, end};
}