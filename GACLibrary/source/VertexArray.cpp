#include <glew.h>
#include "VertexArray.h"
#include <iostream>

/*******************************************************************************************************************************************************
* Vertex array class to create, bind, unbind, and delete vertex arrays. Also creates the associated attribute pointers when adding buffers
*
* Required function descriptions:
*		- glVertexAttribPointer(location of the attribute(unsigned int),
*								size of the attribute(either 1, 2, 3, or 4),
*								type of data(GLenum: like GL_FLOAT),
*								normalized or not(GLboolean),
*								stride, or how long each vertex is in bytes(unsigned int),
*								position of the beginning of the attribute in the vertex(const GLvoid* or void*)
*
* Steps to add vertex buffer in AddBuffer:
*		Step 1: Bind the vertex array
*			- glBindVertexArray
*		Step 2: Bind buffer
*			- Bind
*		Step 3: Enable and describe attributes with calculated offset
*			- glEnableVertexAttribArray
*			- glVertexAttribPointer
*******************************************************************************************************************************************************/

//Default constructor and destructors
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &arrayID);
}

VertexArray::VertexArray(std::vector<Vertex>& vertices)
{
	glGenVertexArrays(1, &arrayID);
	glBindVertexArray(arrayID);
	vbos.push_back(VertexBuffer());
	vbos[0].Bind();
	vbos[0].GenerateData(vertices);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &arrayID);
}

unsigned int VertexArray::GetVAOID()
{
	return arrayID;
}

//Current implementation in use. Takes in the vertices that utilized this vertex array layout. Stores the vbo with the VAO, and utilizes the position and color arrays
//to determine the correct values for the vertex attributes. Still involves hardcoding(unless I can figure out a better way), and may include things like normals in future
//void VertexArray::AddBuffer(std::vector<Vertex>& vertices)
//{
//	glBindVertexArray(arrayID);
//	vbo.GenerateData(vertices);
//	vbo.Bind();
//	unsigned int positionSize = sizeof(vertices[0].position);
//	unsigned int colorSize = sizeof(vertices[0].color);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, positionSize / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, colorSize / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)positionSize);
//}

void VertexArray::AddBuffer(std::vector<Vertex> vertices)
{
	glBindVertexArray(arrayID);
	//VertexBuffer vbo;
	vbos.push_back(VertexBuffer());
	vbos[0].Bind();
	vbos[0].GenerateData(vertices);
}

void VertexArray::AddBuffer(glm::mat4* modelMatrices, unsigned int count)
{
	glBindVertexArray(arrayID);
	vbos.push_back(VertexBuffer());
	vbos[vbos.size() - 1].Bind();
	vbos[vbos.size() - 1].GenerateData(modelMatrices, count);
}

void VertexArray::UpdateBuffer(std::vector<Vertex> vertices, unsigned int buffer)
{
	//unsigned int id = vbos[buffer].GetID();
	//glDeleteBuffers(1, &id);
	//vbos[buffer] = VertexBuffer();
	vbos[buffer].Bind();
	vbos[buffer].GenerateData(vertices);
}

void VertexArray::AddAttribPointer(unsigned int location, unsigned int size, unsigned int vertexSize, unsigned int offset)
{
	glBindVertexArray(arrayID);
	vbos[0].Bind();
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offset));
}

//Need to change parameter vertexSize to attributeSize I believe
void VertexArray::AddAttribPointer(unsigned int location, unsigned int size, unsigned int vertexSize, unsigned int offset, unsigned int buffer)
{
	glBindVertexArray(arrayID);
	vbos[buffer].Bind();

	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size / sizeof(float), GL_FLOAT, GL_FALSE, vertexSize, (void*)(offset));
}

//Used to bind and unbind the VAO itself, not VBOs
void VertexArray::Bind() const
{
	glBindVertexArray(arrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
