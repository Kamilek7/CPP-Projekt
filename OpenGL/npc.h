#ifndef NPC_H_

#define NPC_H_

#include "physicsObject.h"
class NPC :public physicsObject
{
public:
	NPC(const char* name, modelImporter* importer, Physics* phys) :physicsObject(name, importer, phys)
	{
		this->disableRotation();
	}
};
#endif 
