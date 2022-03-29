#pragma once
#include "Vertex.h"

//Class description in cpp file
class VertexBuffer
{
private:
	unsigned int bufferID;

public:
	VertexBuffer(unsigned int size, const void* data);
	VertexBuffer(std::vector<Vertex> vertices);
	//Add constructor that addes its own vertex buffer, and just takes in the vector of vertices
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};