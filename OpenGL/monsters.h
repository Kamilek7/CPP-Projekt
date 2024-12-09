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
	void collidedWith(Body* bd)
	{
		((physicsObject*)(bd->getUserData()))->collidedWithMonster();
	}
	void process(float dt, Shader& shader, Camera& camera)
	{
		if (this->isDead())
		{
			this->phys->world->destroyRigidBody(this->body);
		}
		else
		{
			this->getInfoFromPhys();
			ingameObject::process(dt, shader, camera);


			if (glm::length(*this->playerPos - this->model.translation) < 3)
			{
				this->lookAtPlayer();
				this->followPlayer();
			}

		}
	}
	void followPlayer()
	{
		glm::vec3 temp = glm::normalize(*this->playerPos - this->model.translation);
		Vector3 vec(temp.x, 0, temp.z);

		vec = vec * (glm::length(temp)) / vec.length();
		body->applyLocalForceAtCenterOfMass(vec * 2);
	}
	void collidedWithPlayer()
	{
		this->dead = true;
	}
};
#endif 
