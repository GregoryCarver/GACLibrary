#include "Geometry/Grid.h"

/*******************************************************************************************************************************************************
* Class used to create grid of lines, can be used in things like signifying the x-y plane, or any case a grid may be useful
* 
* TODO: make grid store its own vertices, that way getting vertices is more efficient
*******************************************************************************************************************************************************/
Grid::Grid(unsigned int width, unsigned int length, float transparency)
{
	for (unsigned int i = 0; i < width + 1; i++)
	{
		lines.push_back(Line(-((float)width / 2) + (float)i, 0.0f, -(float)length / 2.0f, -((float)width / 2) + (float)i, 0.0f, (float)length / 2.0f, transparency));
	}

	for (unsigned int i = 0; i < length + 1; i++)
	{
		lines.push_back(Line(-(float)width / 2, 0.0f, -((float)length / 2.0f) + (float)i, (float)width / 2, 0.0f, -((float)length / 2.0f) + (float)i, transparency));
	}
}

std::vector<Vertex> Grid::GetVertices()
{
	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		vertices.push_back(lines[i].GetStart());
		vertices.push_back(lines[i].GetEnd());
	}

	return vertices;
}

unsigned int Grid::GetVAO()
{
	return VAO;
}

void Grid::SetVAO(unsigned int VAOID)
{
	this->VAO = VAOID;
}

void Grid::Transform(glm::mat4 transformationMatrix)
{
	for (Line& line : lines)
	{
		line.Transform(transformationMatrix);
	}
}