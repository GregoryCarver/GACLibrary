#pragma once
#include "VertexBuffer.h"
#include "ElementBuffer.h"

//Vertex array class to create, bind, unbind, and delete vertex arrays. Also creates the associated attribute pointers when adding buffers. Class description in cpp file
class VertexArray
{
private:
	unsigned int arrayID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vbo, unsigned int attribCount);
	void AddBuffer(VertexBuffer& vbo);
	void AddBuffer(std::vector<Vertex>& vertices);
	void Bind() const;
	void Unbind() const;
};

