#ifndef BOARD_H
#define BOARD_H
	
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
#include "room.h"
#include <cstdlib>
#include <ctime>
#include "collisionListener.h"

class GameComponents
{
	int WINDOW_WIDTH = 1000;
	int WINDOW_HEIGHT = 1000;
	int mode = 1;
	unsigned int MAX_FPS = 120;
	double fpsTime = 1 / double(MAX_FPS);
	modelImporter importer;
	Shader shaderProgram;
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.1f, 1.0f, 0.5f);
	Camera camera;
	std::vector <ingameObject*> objects;
	std::vector <Room*> rooms;

	Physics phys;

	double previousTime = 0;
	double duration = 0;
	double Clock = 0;
	double current = 0;

	MyCollisionListener listener;

public:
	GLFWwindow* window;

	GameComponents();
	
	void render();
	void end();
};


#endif