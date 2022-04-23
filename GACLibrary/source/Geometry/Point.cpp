#include "Geometry/Point.h"

Point::Point(glm::vec3 position, float pointSize)
{
	this->position = position;

	vertices.push_back(Vertex(position.x - (pointSize / 2.0f), position.y, position.z));
	vertices.push_back(Vertex(position.x + (pointSize / 2.0f), position.y, position.z));
	vertices.push_back(Vertex(position.x, position.y - (pointSize / 2.0f), position.z));
	vertices.push_back(Vertex(position.x, position.y + (pointSize / 2.0f), position.z));
	vertices.push_back(Vertex(position.x, position.y, position.z - (pointSize / 2.0f)));
	vertices.push_back(Vertex(position.x, position.y, position.z + (pointSize / 2.0f)));
}

std::vector<Vertex> Point::GetVertices()
{
	return vertices;
}

glm::vec3 Point::GetPosition()
{
	return position;
}

void Point::Transform(glm::mat4 transformationMatrix)
{
	for (Vertex& vertex : vertices)
	{
		vertex.Transform(transformationMatrix);
	}
}