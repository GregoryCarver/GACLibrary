#pragma once
#include "VertexBuffer.h"
#include "ElementBuffer.h"

//Vertex array class to create, bind, unbind, and delete vertex arrays. Also creates the associated attribute pointers when adding buffers. Class description in cpp file
class VertexArray
{
private:
	unsigned int arrayID;
	std::vector<VertexBuffer> vbos;

public:
	VertexArray();
	VertexArray(std::vector<Vertex>& vertices);
	~VertexArray();

	unsigned int GetVAOID();

	//Add buffers are sort of experimental
	//void AddBuffer(VertexBuffer& vbo, unsigned int attribCount);
	//void AddBuffer(VertexBuffer& vbo);
	//void AddBuffer(std::vector<Vertex>& vertices);
	void AddBuffer(glm::mat4* modelMatrices, unsigned int count);
	void AddBuffer(std::vector<Vertex> vertices);
	void UpdateBuffer(std::vector<Vertex> vertices, unsigned int buffer);

	void AddAttribPointer(unsigned int location, unsigned int size, unsigned int vertexSize, unsigned int offset);
	void AddAttribPointer(unsigned int location, unsigned int size, unsigned int vertexSize, unsigned int offset, unsigned int buffer);

	void Bind() const;
	void Unbind() const;
};

