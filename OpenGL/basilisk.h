#ifndef BASILISK_H_

#define BASILISK_H_

#include "monsters.h"
class Basilisk :public Monster
{
public:
	Basilisk(modelImporter* importer, Physics* phys) : Monster("resources/basilisk/c3270.obj", importer, phys, glm::vec3(0.1, 0.1, 0.1))
	{
		double scale = 0.5;
		this->model.scale = glm::vec3(scale, scale, scale);
	}
};
#endif 
