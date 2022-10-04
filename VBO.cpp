#include"VBO.h"

VBO::VBO(std::vector<Vertex>& vertices)
{
	//Generate with 1 Object
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// Bind the VBO specifying it's a GL_ARRAY_BUFFER
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Bind to 0 so that we don't accidentally modify it
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Deletes the VBO Object
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}