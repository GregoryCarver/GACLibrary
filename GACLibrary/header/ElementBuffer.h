#pragma once

//Element buffer class to create, bind, unbind, and delete element buffers. Class description in cpp file
class ElementBuffer
{
private:
	unsigned int bufferID;

public:
	ElementBuffer(unsigned int size, const void* data);
	~ElementBuffer();

	void Bind() const;
	void Unbind() const;
};

