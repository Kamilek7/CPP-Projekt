#ifndef BOARD_H
#define BOARD_H
	
#include "room.h"
#include <cstdlib>
#include <ctime>


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
	std::vector <Room*> rooms;

	Physics phys;

	double previousTime = 0;
	double duration = 0;
	double Clock = 0;
	double current = 0;

	

public:
	GLFWwindow* window;

	GameComponents();
	
	void render();
	void end();
};


#endif