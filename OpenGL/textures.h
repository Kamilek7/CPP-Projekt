#ifndef TEXTURES_H
#define TEXTURES_H
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaders.h"

class Texture
{
public:
	int widthImg;
	int heightImg;
	GLuint texture;
	const char* type;
	const char* dir;
	GLuint unit;

	Texture() {};
	Texture(const char* file, const char* texType, GLuint slot);
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void bind();
	void unbind();
	void remove();
};
#endif