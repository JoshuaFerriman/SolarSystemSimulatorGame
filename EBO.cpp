#include"EBO.h"


EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	//Generate with 1 Object
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Make the EBO the current Element Array Object by binding it
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Bind to 0 so that we don't accidentally modify it
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Deletes the EBO Object
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}