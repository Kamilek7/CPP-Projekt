#ifndef NPC_H_

#define NPC_H_

#include "physicsObject.h"
class NPC :public physicsObject
{
protected:
	bool dead;
	glm::vec3* playerPos;
public:
	NPC(const char* name, modelImporter* importer, Physics* phys, glm::vec3 size) :physicsObject(name, importer, phys, size)
	{
		playerPos = new glm::vec3(0, 0, 0);
		dead = false;
		this->disableRotation();
		this->body->setLinearDamping(5);
	}
	bool isDead()
	{
		return dead;
	}
	void getInfoFromPhys()
	{
		InfoPack pack = phys->getInfoOnBody(this->body);

		this->model.translation = pack.position;

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

			
			if (glm::length(*this->playerPos - this->model.translation) < 1.5)
			{
				this->lookAtPlayer();
			}
			
		}
	}

	void lookAtPlayer()
	{
		glm::vec3 temp = *this->playerPos - this->model.translation;
		glm::vec3 temp1 = glm::vec3(temp.x, 0, temp.z);
		glm::vec3 test = glm::vec3(1, 0, 0);

		float angle = acos(glm::dot(test, temp1) / (glm::length(test) * glm::length(temp1)));

		if (temp.z > 0)
		{
			angle = - angle;
		}

		angle +=  asin(1);

		glm::quat rot = glm::angleAxis(angle, glm::vec3(0.f, 1.f, 0.f));

		this->model.rotation = rot;
	}

	void setPlayerLocation(glm::vec3* pos)
	{
		this->playerPos = pos;
	}
};
#endif 