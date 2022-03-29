#include <glew.h>
#include "VertexArray.h"

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

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &arrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &arrayID);
}

void VertexArray::AddBuffer(VertexBuffer& vbo, unsigned int attribCount)
{
	unsigned int offset = 0;
	glBindVertexArray(arrayID);
	vbo.Bind();
	for (unsigned int i = 0; i < attribCount; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)offset);
		offset += 3 * sizeof(float);
	}
}

void VertexArray::AddBuffer(VertexBuffer& vbo)
{
	unsigned int offset = 0;
	glBindVertexArray(arrayID);
	vbo.Bind();
	unsigned int attribCount = 2; //Derived from the Vertex struct(when set to 2, the Vertex was position and color, or 7 floats; may change in future)
	unsigned int vertexFloatCount = 7;
	for (unsigned int i = 0; i < attribCount; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, vertexFloatCount * sizeof(float), (void*)offset);
		offset += 3 * sizeof(float);
	}
}

void VertexArray::AddBuffer(std::vector<Vertex>& vertices)
{
	glBindVertexArray(arrayID);
	VertexBuffer vbo = VertexBuffer(vertices);
	vbo.Bind();
	unsigned int vertexFloatCount = 7;

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexFloatCount * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexFloatCount * sizeof(float), (void*)(3 * sizeof(float)));
}

void VertexArray::Bind() const
{
	glBindVertexArray(arrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
