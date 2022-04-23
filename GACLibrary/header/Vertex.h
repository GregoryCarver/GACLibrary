#pragma once

#include <vector>
#include <glm.hpp>

//Vertex object to contain vertex attributes such as: position, colors, and well be expanded eventually(or maybe another type???) with normals and alike
struct Vertex
{
	//float x, y, z, r, g, b, a;
	float position[3];
	float color[4];

	Vertex();
	Vertex(float x, float y, float z, float a = 1.0f);
	Vertex(float x, float y, float z, float r, float g, float b);
	Vertex(float x, float y, float z, float r, float g, float b, float a);

	float GetX();
	float GetY();
	float GetZ();

	float GetR();
	float GetG();
	float GetB();
	float GetA();

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	void SetR(float r);
	void SetG(float g);
	void SetB(float b);
	void SetA(float a);

	void Transform(glm::mat4 transformationMatrix);
};
