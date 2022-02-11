#include <glew.h>
#include "VertexBuffer.h"

/*******************************************************************************************************************************************************
* Vertex buffer class to create, bind, unbind, and delete vertex buffers
*
* Function descriptions (that I need):
*		- glBindBuffer(target where buffer is bound(GLenum),
*					   buffer(unsigned int)
*		- glBufferData(target where buffer is bound(Glenum),
*					   size in bytes of buffer(unsigned int),
*					   data buffer(const void*),
*					   expected usage pattern(GLenum)
*
* Steps to create vertex buffer in constructor:
*		Step 1: Generate buffer
*			- glGenBuffers
*		Step 2: Bind buffer
*			- glBindBuffer
*		Step 3: Pass buffer data
*			-glBufferData
*******************************************************************************************************************************************************/

VertexBuffer::VertexBuffer(unsigned int size, const void* data)
{
	//Step 1: Generate buffer
	glGenBuffers(1, &bufferID);
	//Step 2: Bind Buffer
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	//Step 3: Pass buffer data
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &bufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
