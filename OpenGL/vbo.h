#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include<glad/glad.h>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
};

class VBO
{
public:
	GLuint buffer;
	VBO(std::vector<Vertex>& vertices);
	void bind();
	void unbind();
	void remove();
};

#endif