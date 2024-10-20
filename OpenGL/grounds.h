#ifndef GROUNDS_H_

#define GROUNDS_H_

#include "nonPhysicsObject.h"
class Grounds:public nonPhysicsObject
{
public:
	Grounds(modelImporter* importer) :nonPhysicsObject("resources/ground2/scene.gltf", importer) 
	{ 
		double scale = 0.04;
		this->model.scale = glm::vec3(scale, scale, scale); 
	}
};
#endif 
