#ifndef PLATFORM_H_
#define PLATFORM_H_
#include "physicsObject.h"

class Platform :public physicsObject
{
public:
	Platform(modelImporter* importer, Physics* phys, glm::vec3 size) :physicsObject("resources/colliderCube/flop.gltf", importer, phys, size, false)
	{
		this->model.scale = size;
	}
	void process(float dt, Shader& shader, Camera& camera)
	{
		ingameObject::process(dt, shader, camera);
	}
};
#endif
