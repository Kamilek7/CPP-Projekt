#ifndef PHYSICALOBJECT_H_

#define PHYSICALOBJECT_H_

#include "object.h"
class physicsObject :public ingameObject
{
public:
	physicsObject(const char* name, modelImporter* importer) :ingameObject(name, importer) {};
};
#endif 
