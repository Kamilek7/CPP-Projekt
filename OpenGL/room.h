#ifndef ROOM_H_

#define ROOM_H_
#include "wall.h"
#include "platform.h"

class Room
{
	std::vector <ingameObject*> objects;
	std::vector <Wall*> walls;
	std::vector <Platform*> platforms;
	modelImporter* importer;
	Physics* phys;

public:
	Room(glm::vec3 position, glm::vec3 size, modelImporter* importer, Physics* phys)
	{
		this->importer = importer;
		this->phys = phys;
		this->createFloor(position, glm::vec3(size.x, 0.1, size.z));
		this->createFloor(glm::vec3(position.x, position.y +size.y, position.z), glm::vec3(size.x, 0.1, size.z));

		this->createWall(glm::vec3(position.x, position.y + size.y/2.0, position.z+size.z/2.0), glm::vec3(size.x, size.y, 0.1));
		this->createWall(glm::vec3(position.x, position.y + size.y / 2.0, position.z -size.z / 2.0), glm::vec3(size.x, size.y, 0.1));

		this->createWall(glm::vec3(position.x + size.x / 2.0, position.y + size.y / 2.0, position.z), glm::vec3(0.1, size.y, size.z));
		this->createWall(glm::vec3(position.x - size.x / 2.0, position.y + size.y / 2.0, position.z), glm::vec3(0.1, size.y, size.z));

	}
	void createFloor(glm::vec3 position, glm::vec3 size)
	{
		platforms.push_back(new Platform(importer, phys, size));
		platforms[platforms.size() - 1]->translate(position.x, position.y, position.z);
	}
	void createWall(glm::vec3 position, glm::vec3 size)
	{
		walls.push_back(new Wall(importer, phys, size));
		walls[walls.size() - 1]->translate(position.x, position.y, position.z);
	}

	void process(float dt, Shader& shader, Camera& camera)
	{
		for (int i = 0; i < walls.size(); i++)
		{
			walls[i]->process(dt, shader, camera);
		}
		for (int i = 0; i < platforms.size(); i++)
		{
			platforms[i]->process(dt, shader, camera);
		}
	}
};

#endif