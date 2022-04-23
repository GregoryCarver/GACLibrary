#include <glew.h>
#include <iostream>
#include "VertexBuffer.h"

/*******************************************************************************************************************************************************
* Vertex buffer class to create, bind, unbind, and delete vertex buffers                                                                               *
*																		                                                                               *
* Function descriptions (that I need):									                                                                               *
*		- glBindBuffer(target where buffer is bound(GLenum),			                                                                               *
*					   buffer(unsigned int)								                                                                               *
*		- glBufferData(target where buffer is bound(Glenum),			                                                                               *
*					   size in bytes of buffer(unsigned int),			                                                                               *
*					   data buffer(const void*),						                                                                               *
*					   expected usage pattern(GLenum)					                                                                               *
*																		                                                                               *
* Steps to create vertex buffer in constructor:							                                                                               *
*		Step 1: Generate buffer											                                                                               *
*			- glGenBuffers												                                                                               *
*		Step 2: Bind buffer												                                                                               *
*			- glBindBuffer												                                                                               *
*		Step 3: Pass buffer data										                                                                               *
*			-glBufferData												                                                                               *
*******************************************************************************************************************************************************/

VertexBuffer::VertexBuffer()
{
	//Step 1: Generate buffer
	glGenBuffers(1, &bufferID);
	//Step 2: Bind Buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

//Constructor used to initialize VBO using an array of vertices
VertexBuffer::VertexBuffer(unsigned int size, const void* data)
{
	//Step 1: Generate buffer
	glGenBuffers(1, &bufferID);
	//Step 2: Bind Buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//Step 3: Pass buffer data
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

//Constructor used to initialize VBO with vector of vertices
VertexBuffer::VertexBuffer(std::vector<Vertex> vertices)
{
	//Step 1: Generate buffer
	glGenBuffers(1, &bufferID);
	//Step 2: Bind Buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//Step 3: Pass buffer data
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}

//Destructor
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &bufferID);
}

unsigned int VertexBuffer::GetID()
{
	return bufferID;
}

//Functions used to bind and unbind the VBO itself
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Default VAO constructor creates a default VBO, so this is used to populate that VBO's data.
void VertexBuffer::GenerateData(std::vector<Vertex> vertices)
{
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}

void VertexBuffer::GenerateData(glm::mat4* modelMatrices, unsigned int count)
{
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
}
