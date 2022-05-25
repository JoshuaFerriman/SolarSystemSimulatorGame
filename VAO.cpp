#include"VAO.h"

VAO::VAO()
{
	//Generate with 1 Object
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Make the VAO the current Vertex Array Object by binding it
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Bind to 0 so that we don't accidentally modify it
void VAO::Unbind()
{
	glBindVertexArray(0);
}

//Deletes the VAO Object
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}