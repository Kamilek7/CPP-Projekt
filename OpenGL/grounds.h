#ifndef GROUNDS_H_

#define GROUNDS_H_

#include "physicsObject.h"
class Grounds:public physicsObject
{
public:
	Grounds(modelImporter* importer, Physics* phys) :physicsObject("resources/ground2/scene.gltf", importer, phys, glm::vec3(10.0,1.0,10.0), false)
	{ 
		double scale = 0.04;
		this->model.scale = glm::vec3(scale*4, scale, scale); 
	}
};
#endif 
