#ifndef NONPHYSICALOBJECT_H_

#define NONPHYSICALOBJECT_H_

#include "object.h"
class nonPhysicsObject:public ingameObject
{
public:
	nonPhysicsObject(const char* name, modelImporter* importer) :ingameObject(name, importer) {};
};
#endif 
