#ifndef FIGHTER_H_

#define FIGHTER_H_

#include "humans.h"
class Fighter :public Human
{
public:
	Fighter(modelImporter* importer, Physics* phys) : Human("resources/fighter/scene.gltf", importer, phys, glm::vec3(0.05, 0.05, 0.01))
	{
		double scale = 0.2;
		this->model.scale = glm::vec3(scale, scale, scale);
		this->model.linOffset.y = 0.2;
	}
};
#endif 
