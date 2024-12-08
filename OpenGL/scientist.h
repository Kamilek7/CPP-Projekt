#ifndef SCIENTIST_H_

#define SCIENTIST_H_

#include "humans.h"
class Scientist :public Human
{
public:
	Scientist(modelImporter* importer, Physics* phys) : Human("resources/kleiner/klener.obj", importer, phys, glm::vec3(0.001,0.1,0.001))
	{
		double scale = 0.005;
		this->model.scale = glm::vec3(scale, scale, scale);
	}
};
#endif 
