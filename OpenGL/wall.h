#ifndef BRICKWALL_H_

#define BRICKWALL_H_

#include "physicsObject.h"
class Wall:public physicsObject {
public:
	Wall(modelImporter* importer, Physics* phys, glm::vec3 size) :physicsObject("resources/brickWall/mur.gltf", importer, phys, size, false)
	{
		this->model.scale = size;
		glm::vec2 scaler = glm::vec2(size.x, size.y);
		if (size.x < size.z)
			scaler.x = size.z;
		else if (size.y < size.z)
			scaler.y = size.z;
		double SCALE = 0.02;
		scaler = glm::vec2(scaler.x * SCALE, scaler.y * SCALE);
		for (int i = 0; i < this->model.meshes.size(); i++)
			this->model.meshes[i].unwrapTexCoords(scaler);
	}
	void process(float dt, Shader& shader, Camera& camera)
	{
		ingameObject::process(dt, shader, camera);
	}
};

#endif
