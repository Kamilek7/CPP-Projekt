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
	float intensity = 1.0;

};
#endif // !LIGHT_H_
