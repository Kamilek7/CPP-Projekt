#ifndef HUMANS_H_

#define HUMANS_H_

#include "npc.h"
class Human :public NPC
{
public:
	Human(const char* name, modelImporter* importer, Physics* phys) : NPC(name, importer, phys)
	{
		double scale = 0.005;
		this->model.scale = glm::vec3(scale, scale, scale);
	}
};
#endif 
