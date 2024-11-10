#ifndef GROUNDS_H_

#define GROUNDS_H_

#include "physicsObject.h"
class Grounds:public physicsObject
{
public:
	Grounds(modelImporter* importer, Physics* phys) :physicsObject("resources/ground2/scene.gltf", importer, phys, glm::vec3(10.0,0.01,10.0), false)
	{ 
		double scale = 0.04;
		this->model.translation.y = 0.05;
		this->model.scale = glm::vec3(scale*4, scale, scale); 
	}
	void process(float dt, Shader& shader, Camera& camera)
	{
		ingameObject::process(dt, shader, camera);
	}
};
#endif 
