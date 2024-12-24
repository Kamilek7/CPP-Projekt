#ifndef ROOM_H_

#define ROOM_H_

#include "graph.h"
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
#include "light.h"
class Room
{
	std::vector <physicsObject*> objects;
	std::vector <Wall*> walls;
	std::vector <Platform*> platforms;
	std::vector <Light*> lights;

	modelImporter* importer;
	Physics* phys;
	GLFWwindow* window;

	Shader shaderProgram;
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.1f, 1.0f, 0.5f);

	Player* player;
	GraphMap map;
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

		this->setLights();

		this->phys->world->setEventListener(&listener);
	}
	Room()
	{

	}
	void generateRoom()
	{


		for (int y = map.dimensions[3]; y >= map.dimensions[2]; y--)
		{
			for (int x = map.dimensions[0]; x <= map.dimensions[1]; x++)
			{

				std::pair <int, int> pos = std::make_pair(x, y);
				if (map.map.find(pos) != map.map.end())
				{
					this->createFloor(glm::vec3(2*size.x*double(x), position.y, 2*size.z*double(y)), glm::vec3(size.x, 0.05, size.z));
					this->createFloor(glm::vec3(2*size.x*double(x), position.y + 2*size.y, 2*size.z*double(y)), glm::vec3(size.x, 0.05, size.z));
					if (map.map[pos]->whereParent == 0 || map.map[pos]->directions[0] != -1)
					{
						this->createWall(glm::vec3(2*size.x * double(x) + 5*size.x/8, position.y + size.y, 2*size.z * double(y) + size.z), glm::vec3(size.x*3/8, size.y, 0.1));
						this->createWall(glm::vec3(2 * size.x * double(x) - 5 * size.x / 8, position.y + size.y, 2 * size.z * double(y) + size.z), glm::vec3(size.x * 3 / 8, size.y, 0.1));
					}
					else
					{
						this->createWall(glm::vec3(2*size.x * double(x), position.y + size.y, 2*size.z * double(y) + size.z), glm::vec3(size.x, size.y, 0.1));
					}

					if (map.map[pos]->whereParent == 1 || map.map[pos]->directions[1] != -1)
					{
						this->createWall(glm::vec3(2 * size.x * double(x) + 5 * size.x / 8, position.y + size.y, 2 * size.z * double(y) - size.z), glm::vec3(size.x * 3 / 8, size.y, 0.1));
						this->createWall(glm::vec3(2 * size.x * double(x) - 5 * size.x / 8, position.y + size.y, 2 * size.z * double(y) - size.z), glm::vec3(size.x * 3 / 8, size.y, 0.1));
					}
					else
					{
						this->createWall(glm::vec3(2*size.x * double(x), position.y + size.y, 2*size.z * double(y) - size.z), glm::vec3(size.x, size.y, 0.1));
					}

					if (map.map[pos]->whereParent == 2 || map.map[pos]->directions[2] != -1)
					{
						this->createWall(glm::vec3(2 * size.x * double(x) + size.x, position.y + size.y, 2 * size.z * double(y) + 5 * size.z / 8), glm::vec3(0.1, size.y, size.z * 3 / 8));
						this->createWall(glm::vec3(2 * size.x * double(x) + size.x, position.y + size.y, 2 * size.z * double(y) - 5 * size.z / 8), glm::vec3(0.1, size.y, size.z * 3 / 8));
					}
					else
					{
						this->createWall(glm::vec3(2 * size.x * double(x) + size.x, position.y + size.y, 2 * size.z * double(y)), glm::vec3(0.1, size.y, size.z));
					}

					if (map.map[pos]->whereParent == 3 || map.map[pos]->directions[3] != -1)
					{
						this->createWall(glm::vec3(2 * size.x * double(x) - size.x, position.y + size.y, 2 * size.z * double(y) + 5 * size.z / 8), glm::vec3(0.1, size.y, size.z * 3 / 8));
						this->createWall(glm::vec3(2 * size.x * double(x) - size.x, position.y + size.y, 2 * size.z * double(y) - 5 * size.z / 8), glm::vec3(0.1, size.y, size.z * 3 / 8));
					}
					else
					{
						this->createWall(glm::vec3(2 * size.x * double(x) - size.x, position.y + size.y, 2 * size.z * double(y)), glm::vec3(0.1, size.y, size.z));
					}
				}
			}
		}
		


		
	}

	void setLights()
	{
		shaderProgram = Shader("default.vert", "default.frag", map.size);
		shaderProgram.on();

		for (int i = 0; i < map.size; i++)
		{
			glUniform4f(glGetUniformLocation(shaderProgram.program, ( std::string("pointLights[") + std::to_string(i) + std::string( "].lightColor")).c_str()), lights[i]->color.x, lights[i]->color.y, lights[i]->color.z, lights[i]->color.w);
			glUniform3f(glGetUniformLocation(shaderProgram.program, (std::string("pointLights[") + std::to_string(i) + std::string("].position")).c_str()), lights[i]->position.x, lights[i]->position.y, lights[i]->position.z);
		}


	}

	void populateRoom()
	{

		std::cout << map.size;
		for (int y = map.dimensions[3]; y >= map.dimensions[2]; y--)
		{
			for (int x = map.dimensions[0]; x <= map.dimensions[1]; x++)
			{

				std::pair <int, int> pos = std::make_pair(x, y);
				if (map.map.find(pos) != map.map.end())
				{


					lights.push_back(new Light(glm::vec3(2 * size.x * x, 1.5, 2 * size.z * y), lightColor));

					//if (!(std::rand() % 3))
					//{
						//objects.push_back(new Aquamon(importer, phys));
						//objects[objects.size()-1]->translate(0, 1.0, 0);
						//objects[objects.size() - 1]->setPlayerLocation(&this->player->location);
					//}

				}
			}
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

	void process(float dt, Camera& camera)
	{
		player->process(dt, shaderProgram, camera);
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->process(dt, shaderProgram, camera);
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
			walls[i]->process(dt, shaderProgram, camera);
		}
		for (int i = 0; i < platforms.size(); i++)
		{
			platforms[i]->process(dt, shaderProgram, camera);
		}
	}
};

#endif