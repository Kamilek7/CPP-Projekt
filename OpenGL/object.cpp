#include "object.h"

ingameObject::ingameObject(const char* name, modelImporter* importer)
{
	this->time = 0.0;
	this->model = glModel(name, importer);

}

void ingameObject::translate(double x, double y, double z, double scale)
{
	this->model.translation.x += x * scale;
	this->model.translation.y += y * scale;
	this->model.translation.z += z * scale;
}

void ingameObject::scaleBy(double scale)
{
	this->model.scale *= scale;
}

void ingameObject::scaleTo(double x, double y, double z)
{
	this->model.scale.x = x;
	this->model.scale.y = y;
	this->model.scale.z = z;
}


void ingameObject::process(float dt, Shader& shader, Camera &camera)
{
	this->time += dt;
	glUniform2f(glGetUniformLocation(shader.program, "texScaler"), this->texScale.x, this->texScale.y);
	this->model.draw(shader, camera, dt);
}