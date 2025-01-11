#ifndef MONSTERS_H_
#define MONSTERS_H_

#include "npc.h"
#include <chrono>

class Monster : public NPC
{
private:
    int lives = 1; // Liczba zyc potwora (domyslnie 1)
	double cooldown = 3;
	double jumpCooldown = 2;
	double heightOffset= 0.09f;

public:
	Monster(const char* name, modelImporter* importer, Physics* phys, glm::vec3 size) : NPC(name, importer, phys, size)
	{
		double scale = 0.005;
		this->model.scale = glm::vec3(scale, scale, scale);
	}
	void collidedWith(Body* bd)
	{
		glm::vec3 dif = ((physicsObject*)(bd->getUserData()))->model.translation - this->model.translation;

		Vector3 vec;
		vec.x = dif.x * 25;
		vec.y = 80*(dif.y-heightOffset);
		vec.z = 25*dif.z;

		((physicsObject*)(bd->getUserData()))->body->applyLocalForceAtCenterOfMass(vec*200);
		((physicsObject*)(bd->getUserData()))->collidedWithMonster();
	}

	virtual void additionalMovement(float dt)
	{

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
			if (this->cooldown >= 0)
			{
				this->cooldown -= dt;
			}
			if (this->jumpCooldown >= 0)
			{
				this->jumpCooldown -= dt;
			}

			this->additionalMovement(dt);

			if (glm::length(*this->playerPos - this->model.translation) < 5)
			{
				this->lookAtPlayer();
				this->followPlayer();
				if (this->body->getLinearVelocity().y <= 0.1 && this->jumpCooldown<=0)
				{
					this->body->applyLocalForceAtCenterOfMass(Vector3(0.0, 500.0, 0.0));
					this->jumpCooldown = 2;
				}
			}

		}
	}
	void followPlayer()
	{
		glm::vec3 temp = glm::normalize(*this->playerPos - this->model.translation);
		Vector3 vec(temp.x, 0, temp.z);

		vec = vec * (glm::length(temp)) / vec.length();
		body->applyLocalForceAtCenterOfMass(vec * 7);
	}
	void collidedWithPlayer()
	{
		if (this->cooldown <= 0)
		{
			this->cooldown = 3;
			if (--lives <= 0)
			{
				this->dead = true;
			}
		}

	}
};

#endif
