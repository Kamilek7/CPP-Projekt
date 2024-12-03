#ifndef VAO_CLAS_H
#define VAO_CLAS_H

#include"vbo.h"
#include<glad/glad.h>

class VAO
{
public:
	GLuint buffer;
	VAO();
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();
	void remove();
};
#endif