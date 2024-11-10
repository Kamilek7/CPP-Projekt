#ifndef PHYSICS_H
#define PHYSICS_H

#include "reactphysics3d/reactphysics3d.h"
#include "object.h"

struct InfoPack
{
	glm::vec3 position;
	glm::quat orientation;
};


using namespace reactphysics3d;


class Physics
{

	
public:
	PhysicsCommon physicsCommon;
	PhysicsWorld* world;

	Physics()
	{
		world = physicsCommon.createPhysicsWorld();
	};
	RigidBody* linkBody(glm::vec3 size, bool dynamic)
	{
		Vector3 position(0, 0, 0);
		Quaternion orientation = Quaternion::identity();
		Transform transform(position, orientation);
		const Vector3 halfExtents(size.x, size.y, size.z);
		BoxShape* boxShape = physicsCommon.createBoxShape(halfExtents);

		RigidBody* body = world->createRigidBody(transform);

		
		if (!dynamic)
			body->setType(BodyType::STATIC);
		else
			body->setType(BodyType::DYNAMIC);
		Collider* collider;
		collider = body->addCollider(boxShape, transform);
		return body;
	}
	InfoPack getInfoOnBody(RigidBody* body, bool disableRotation)
	{
		const Transform& transform = body->getTransform();
		const Vector3& position = transform.getPosition();
		const Quaternion& orientation = transform.getOrientation();

		InfoPack package;
		glm::vec3 temp;
		temp.x = position.x;
		temp.y = position.y;
		temp.z = position.z;
		package.position = temp;
		if (!disableRotation)
		{
			glm::quat temp1;
			temp1.w = orientation.w;
			temp1.x = orientation.x;
			temp1.y = orientation.y;
			temp1.z = orientation.z;
			package.orientation = temp1;
		}

		return package;
	}
	void process(double timeStep)
	{

		world->update(timeStep);

	}
};
#endif