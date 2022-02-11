#pragma once

//Class description in cpp file
class VertexBuffer
{
private:
	unsigned int bufferID;

public:
	VertexBuffer(unsigned int size, const void* data);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};