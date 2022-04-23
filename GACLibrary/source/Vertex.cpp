#include "Vertex.h"
#include <iostream>

/*******************************************************************************************************************************************************
* Vertex object to contain vertex attributes such as: position, colors, and well be expanded eventually(or maybe another type???) with normals and alike
*******************************************************************************************************************************************************/
Vertex::Vertex()
{
	/*x = y = z = r = 0.0f;
	g = 0.5f;
	b = 0.7f;
	a = 1.0f;*/

	position[0] = position[1] = position[2] = color[0] = 0.0f;
	color[1] = 0.5f;
	color[2] = 0.7f;
	color[3] = 1.0f;
}

Vertex::Vertex(float x, float y, float z, float a)// : r(0.0f), g(0.5f), b(0.7f)
{
	//this->x = x;
	//this->y = y;
	//this->z = z;

	//this->a = a;

	position[0] = x;
	position[1] = y;
	position[2] = z;
	color[0] = 0.0f;
	color[1] = 0.5f;
	color[2] = 0.7f;
	color[3] = a;
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b)// : a(1.0f)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = 1.0f;
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b, float a)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

float Vertex::GetX()
{
	return position[0];
}

float Vertex::GetY()
{
	return position[1];
}

float Vertex::GetZ()
{
	return position[2];
}

float Vertex::GetR()
{
	return color[0];
}

float Vertex::GetG()
{
	return color[1];
}

float Vertex::GetB()
{
	return color[2];
}

float Vertex::GetA()
{
	return color[3];
}

void Vertex::SetX(float x)
{
	position[0] = x;
}
void Vertex::SetY(float y)
{
	position[1] = y;
}
void Vertex::SetZ(float z)
{
	position[2] = z;
}
	 
void Vertex::SetR(float r)
{
	color[0] = r;
}
void Vertex::SetG(float g)
{
	color[1] = g;
}
void Vertex::SetB(float b)
{
	color[2] = b;
}
void Vertex::SetA(float a)
{
	color[3] = a;
}

//Takes a transformation matrix and applies it to the position of the vertex. Can be used to do transformations such as: rotations, translations, and scaling
void Vertex::Transform(glm::mat4 transformationMatrix)
{
	glm::vec3 newPosition = transformationMatrix * glm::vec4(position[0], position[1], position[2], 1.0f);
	position[0] = newPosition.x;
	position[1] = newPosition.y;
	position[2] = newPosition.z;
}