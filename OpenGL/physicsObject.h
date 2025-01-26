#ifndef PHYSICALOBJECT_H_

#define PHYSICALOBJECT_H_

#include "physicsApplied.h"


class physicsObject :public ingameObject
{
protected:
	glm::vec3 size;
	Physics* phys;

public:
	
	RigidBody* body;
	physicsObject(const char* name, modelImporter* importer, Physics* _phys, glm::vec3 size = glm::vec3(0.1,0.1,0.1), bool dynamic = true) :ingameObject(name, importer)
	{
		this->size = size;
		this->phys = _phys;
		this->body = phys->linkBody(size, dynamic);
		this->body->setAngularDamping(reactphysics3d::decimal(1));

		this->body->setUserData((void*)(this));

	};
	void process(float dt, Shader& shader, Camera& camera)
	{
		if (dt != 0)
		{
			this->getInfoFromPhys();
			ingameObject::process(dt, shader, camera);
		}

		
	}
	void getInfoFromPhys()
	{
		InfoPack pack = phys->getInfoOnBody(this->body);
		
		this->model.translation = pack.position;
		this->model.rotation = pack.orientation;

	}
	void translate(double x = 0.0, double y = 0.0, double z = 0.0, double scale = 1.0)
	{
		ingameObject::translate(x, y, z, scale);
		const reactphysics3d::Transform transform = this->body->getTransform();
		Vector3 pos = transform.getPosition();
		Quaternion quat = transform.getOrientation();

		pos.x += x * scale;
		pos.y += y * scale;
		pos.z += z * scale;
		Transform transformNew(pos, quat);
		this->body->setTransform(transformNew);
	}
	void disableRotation()
	{
		body->setAngularLockAxisFactor(Vector3(0, 0, 0));
	}

	virtual void collidedWith(Body* bd) { }
	virtual void collidedWithMonster(int damage) {}
	virtual void collidedWithPlayer() {}
	virtual void setPlayerLocation(glm::vec3* pos) {}
};
#endif 