#include "Buffer.h"

Buffer::Buffer(unsigned int type, unsigned int size, void* data)
{
	this->type = type;
	this->size = size;
	glGenBuffers(1, &this->ID);
	glBindBuffer(this->type, this->ID);
	glBufferData(this->type, this->size, data, GL_STATIC_DRAW);
}

//Buffer::Buffer(unsigned int type, unsigned int size)
//{
//	this->type = type;
//	this->size = size;
//	glGenVertexArrays(1, &this->ID);
//	glBindBuffer(this->type, this->ID);
//}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &this->ID);
}

void Buffer::bind()
{
	glBindBuffer(this->type, this->ID);
}

void Buffer::unbind()
{
	glBindBuffer(this->type, 0);
}

void Buffer::updateData(void* data)
{
	glBindBuffer(this->type, this->ID);
	glBufferSubData(this->type, 0, this->size, data);
}

unsigned int Buffer::getID()
{
	return this->ID;
}

unsigned int Buffer::getSize()
{
	return this->size;
}

unsigned int Buffer::getType()
{
	return this->type;
}
