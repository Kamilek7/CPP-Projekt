#ifndef NPC_H_

#define NPC_H_

#include "physicsObject.h"
class NPC :public physicsObject
{
public:
	NPC(const char* name, modelImporter* importer, Physics* phys, glm::vec3 size) :physicsObject(name, importer, phys, size)
	{
		this->disableRotation();
	}
};
#endif 
