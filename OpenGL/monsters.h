#ifndef MONSTERS_H_

#define MONSTERS_H_

#include "npc.h"
class Monster :public NPC
{
public:
	Monster(const char* name, modelImporter* importer, Physics* phys, glm::vec3 size) : NPC(name, importer, phys, size)
	{
		double scale = 0.005;
		this->model.scale = glm::vec3(scale, scale, scale);
	}
};
#endif 
