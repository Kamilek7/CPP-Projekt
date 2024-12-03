#ifndef OBJECT_H
#define OBJECT_H

#include "model.h"

class ingameObject
{
protected:
	float time;
	glModel model;
	

public:

	int ID;
	ingameObject(const char* name, modelImporter* importer);
	virtual void translate(double x=0.0, double y=0.0, double z=0.0, double scale=1.0);

	virtual void scaleBy(double scale=1.0);

	virtual void scaleTo(double x, double y, double z);

	virtual void process(float dt, Shader& shader, Camera& camera);
	virtual bool isDead() { return false; }

};
#endif
