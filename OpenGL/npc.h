#ifndef NPC_H_

#define NPC_H_

#include "physicsObject.h"
class NPC :public physicsObject
{
protected:
	bool dead;
public:
	NPC(const char* name, modelImporter* importer, Physics* phys, glm::vec3 size) :physicsObject(name, importer, phys, size)
	{
		dead = false;
		this->disableRotation();
	}
	bool isDead()
	{
		return dead;
	}
	void process(float dt, Shader& shader, Camera& camera)
	{
		if (this->isDead())
		{
			this->phys->world->destroyRigidBody(this->body);
		}
		else
		{
			physicsObject::process(dt, shader, camera);
		}
		


	}

};
#endif 
