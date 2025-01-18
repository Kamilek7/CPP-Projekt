#ifndef PLATFORM_H_
#define PLATFORM_H_
#include "physicsObject.h"

class Platform :public physicsObject
{
public:
	Platform(modelImporter* importer, Physics* phys, glm::vec3 size) :physicsObject("resources/floor/floor.gltf", importer, phys, size, false)
	{
		this->model.scale = size;
		glm::vec2 scaler = glm::vec2(size.x, size.z);
		float SCALE = 6;
		this->texScale = glm::vec2(scaler.y, scaler.y) * SCALE;

	}
	void process(float dt, Shader& shader, Camera& camera)
	{
		ingameObject::process(dt, shader, camera);
	}
};
#endif