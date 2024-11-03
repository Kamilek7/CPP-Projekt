#ifndef SCIENTIST_H_

#define SCIENTIST_H_

#include "humans.h"
class Scientist :public Human
{
public:
	Scientist(modelImporter* importer, Physics* phys) : Human("resources/kleiner/klener.obj", importer, phys)
	{
		double scale = 0.005;
		this->model.scale = glm::vec3(scale, scale, scale);
	}
};
#endif 
