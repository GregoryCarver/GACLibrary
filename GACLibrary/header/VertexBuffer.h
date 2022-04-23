#pragma once
#include "Vertex.h"

//Vertex buffer class to create, bind, unbind, and delete vertex buffers. Class description in cpp file
class VertexBuffer
{
private:
	unsigned int bufferID;

public:
	VertexBuffer();
	VertexBuffer(unsigned int size, const void* data);
	VertexBuffer(std::vector<Vertex> vertices);
	~VertexBuffer();

	unsigned int GetID();

	void Bind() const;
	void Unbind() const;
	void GenerateData(std::vector<Vertex> vertices);
	void GenerateData(glm::mat4* modelMatrices, unsigned int count);
};