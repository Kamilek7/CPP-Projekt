#ifndef BOARD_H
#define BOARD_H
	
#include "room.h"



class GameComponents
{
	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 600;
	int REMEMBERED_WIDTH = WINDOW_WIDTH;
	int REMEMBERED_HEIGHT = WINDOW_HEIGHT;
	int mode = 1;
	unsigned int MAX_FPS = 120;
	double fpsTime = 1 / double(MAX_FPS);
	modelImporter importer;
	Camera camera;
	Room* mainLocation;

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