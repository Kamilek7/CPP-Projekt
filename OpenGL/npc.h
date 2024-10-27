#ifndef NPC_H_

#define NPC_H_

#include "physicsObject.h"
class NPC :public physicsObject
{
public:
	NPC(modelImporter* importer) :physicsObject("resources/kleiner/klener.obj", importer)
	{
		double scale = 0.005;
		this->model.scale = glm::vec3(scale, scale, scale);
	}
};
#endif 
