#include "Geometry/DoubleArrow.h"

DoubleArrow::DoubleArrow(Vertex start, Vertex end)
{
	float arrowHeadSize = 0.025f;

	vertices.push_back(Vertex(start.GetX() - arrowHeadSize, start.GetY() - arrowHeadSize, start.GetZ()));
	vertices.push_back(Vertex(start.GetX(), start.GetY(), start.GetZ()));
	vertices.push_back(Vertex(start.GetX() + arrowHeadSize, start.GetY() - arrowHeadSize, start.GetZ()));
	vertices.push_back(Vertex(start.GetX(), start.GetY(), start.GetZ()));
	vertices.push_back(Vertex(start.GetX(), start.GetY(), start.GetZ()));
	vertices.push_back(Vertex(end.GetX(), end.GetY(), end.GetZ()));
	vertices.push_back(Vertex(end.GetX() - arrowHeadSize, end.GetY() + arrowHeadSize, end.GetZ()));
	vertices.push_back(Vertex(end.GetX(), end.GetY(), end.GetZ()));
	vertices.push_back(Vertex(end.GetX() + arrowHeadSize, end.GetY() + arrowHeadSize, end.GetZ()));
	vertices.push_back(Vertex(end.GetX(), end.GetY(), end.GetZ()));
}

std::vector<Vertex> DoubleArrow::GetVertices()
{
	return vertices;
}

void DoubleArrow::Transform(glm::mat4 transformationMatrix)
{
	for (Vertex& vertex : vertices)
	{
		vertex.Transform(transformationMatrix);
	}
}