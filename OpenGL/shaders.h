#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string getContents(const char* filename);

class Shader
{
public:
	GLuint program;
	Shader() {};
	Shader(const char* vertFile, const char* fragFile);

	void on();
	void remove();
};

#endif