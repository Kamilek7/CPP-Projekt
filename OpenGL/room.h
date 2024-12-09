#ifndef ROOM_H_

#define ROOM_H_
#include "wall.h"
#include "platform.h"
#include"grounds.h"
#include "scientist.h"
#include "basilisk.h"
#include "fighter.h"
#include "player.h"
#include "Aquamon.h"
#include "Aquilamon.h"
#include "BlackAqumon.h"
#include "DarkTyrannomon.h"
#include "Tenemon.h"
#include "Tsunomon.h"
#include "collisionListener.h"

class Room
{
	std::vector <physicsObject*> objects;
	std::vector <Wall*> walls;
	std::vector <Platform*> platforms;
	modelImporter* importer;
	Physics* phys;
	GLFWwindow* window;

	Player* player;

	glm::vec3 size;
	glm::vec3 position;

	MyCollisionListener listener;

public:
	Room(glm::vec3 position, glm::vec3 size, modelImporter* importer, Physics* phys, GLFWwindow* window)
	{
		this->size = size;
		this->position = position;

		this->window = window;
		this->importer = importer;
		this->phys = phys;
		this->player = new Player(importer, phys, window);

		this->generateRoom();

		this->populateRoom();

		this->phys->world->setEventListener(&listener);
	}

	void generateRoom()
	{
		this->createFloor(position, glm::vec3(size.x, 0.1, size.z));
		this->createFloor(glm::vec3(position.x, position.y + size.y, position.z), glm::vec3(size.x, 0.1, size.z));

		this->createWall(glm::vec3(position.x, position.y + size.y / 2.0, position.z + size.z / 2.0), glm::vec3(size.x, size.y, 0.1));
		this->createWall(glm::vec3(position.x, position.y + size.y / 2.0, position.z - size.z / 2.0), glm::vec3(size.x, size.y, 0.1));

		this->createWall(glm::vec3(position.x + size.x / 2.0, position.y + size.y / 2.0, position.z), glm::vec3(0.1, size.y, size.z));
		this->createWall(glm::vec3(position.x - size.x / 2.0, position.y + size.y / 2.0, position.z), glm::vec3(0.1, size.y, size.z));

		
	}

	void populateRoom()
	{

		objects.push_back(new Aquamon(importer, phys));
		objects.push_back(new Aquilamon(importer, phys));
		objects.push_back(new BlackAqumon(importer, phys));
		objects.push_back(new Tenemon(importer, phys));
		objects.push_back(new Tsunomon(importer, phys));

		objects.push_back(new Scientist(importer, phys));
		objects.push_back(new Basilisk(importer, phys));
		objects.push_back(new Fighter(importer, phys));

		objects.push_back(new DarkTyrannomon(importer, phys));

		// Pozycjonowanie obiektow
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->translate(-0.8 + double(i * 0.6), 0.2);
			objects[i]->setPlayerLocation(&this->player->location);
		}

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
		player->process(dt, shader, camera);
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->process(dt, shader, camera);
			if (objects[i]->isDead())
			{

				delete objects[i];
				objects[i] = nullptr;
				objects.erase(objects.begin() + i);
				i--;
			}
		}
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