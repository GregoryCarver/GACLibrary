#include <glew.h>
#include "ElementBuffer.h"

//Class description is similiar to what is found in VertexBuffer.cpp
/*******************************************************************************************************************************************************
* Element buffer class to create, bind, unbind, and delete element buffers
*
* Required function descriptions:
*		- glBindBuffer(target where buffer is bound(GLenum),
*					   buffer(unsigned int)
*		- glBufferData(target where buffer is bound(Glenum),
*					   size in bytes of buffer(unsigned int),
*					   data buffer(const void*),
*					   expected usage pattern(GLenum)
*
* Steps to create element buffer in constructor:
*		Step 1: Generate buffer
*			- glGenBuffers
*		Step 2: Bind buffer
*			- glBindBuffer
*		Step 3: Pass buffer data
*			-glBufferData
*******************************************************************************************************************************************************/
ElementBuffer::ElementBuffer(unsigned int size, const void* data)
{
	//Step 1: Generate buffer
	glGenBuffers(1, &bufferID);
	//Step 2: Bind Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	//Step 3: Pass buffer data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &bufferID);
}

void ElementBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void ElementBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}