#include "object.h"

ingameObject::ingameObject(const char* name, modelImporter* importer)
{
	this->time = 0.0;
	this->model = glModel(name, importer);
}

void ingameObject::process(float dt, Shader& shader, Camera &camera)
{
	this->time += dt;

	this->model.translation.x = sin(1.0);
	this->model.draw(shader, camera);
}
