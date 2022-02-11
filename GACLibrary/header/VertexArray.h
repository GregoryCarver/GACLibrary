#pragma once
#include "VertexBuffer.h"
#include "ElementBuffer.h"

//Class description in cpp file
class VertexArray
{
private:
	unsigned int arrayID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vbo, unsigned int attribCount);
	void Bind() const;
	void Unbind() const;
};

