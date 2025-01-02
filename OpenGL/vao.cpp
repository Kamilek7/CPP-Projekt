#include"vao.h"

VAO::VAO()
{
	glGenVertexArrays(1, &buffer);
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.bind();
	if (type == GL_INT)
		glVertexAttribIPointer(layout, numComponents, type, stride, offset);
	else
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}

void VAO::bind()
{
	glBindVertexArray(buffer);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::remove()
{
	glDeleteVertexArrays(1, &buffer);
}