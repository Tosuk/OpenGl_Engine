#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Buffer
{
private:
	unsigned int ID;
	unsigned int type;
	unsigned int size;

public:
	Buffer(unsigned int type, unsigned int size, void* data);
	//Buffer(, unsigned int size);
	~Buffer();
	void bind();
	void unbind();
	void updateData(void* data);
	unsigned int getID();
	unsigned int getSize();
	unsigned int getType();
};

