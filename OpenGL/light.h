#ifndef LIGHT_H_

#define LIGHT_H_

#include "vao.h"
#include "ebo.h"
#include "camera.h"
#include "textures.h"

class Light
{
	glm::vec3 position;
	glm::vec3 color;

	int id;

	float intensity;
	float a;
	float b;
	float c;

	Light()
	{
		static int count = 0;
		id = count;
		count++;
	}
	void process(Shader& shader)
	{

	}
};
#endif // !LIGHT_H_
