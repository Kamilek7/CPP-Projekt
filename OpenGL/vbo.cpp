#include"vbo.h"

VBO::VBO(std::vector<Vertex>&vertices)
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}


void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::remove()
{
	glDeleteBuffers(1, &buffer);
}