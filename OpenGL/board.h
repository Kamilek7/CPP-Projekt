#ifndef BOARD_H
#define BOARD_H
	
#include "room.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class GameComponents
{
	bool paused = false;
	bool escPressed = false;
	int WINDOW_WIDTH = 1000;
	int WINDOW_HEIGHT = 1000;
	int REMEMBERED_WIDTH = WINDOW_WIDTH;
	int REMEMBERED_HEIGHT = WINDOW_HEIGHT;
	int mode = 0;
	unsigned int MAX_FPS = 120;
	double fpsTime = 1 / double(MAX_FPS);
	modelImporter importer;
	Camera camera;
	Room* mainLocation;
	Texture mainMenu;
	ImFont* fontLarger;
	ImFont* fontSmaller;

	Physics phys;

	double previousTime = 0;
	double duration = 0;
	double Clock = 0;
	double current = 0;

	void drawMap(double zoom);
	void drawRoom(std::pair<int, int> pos, double zoom);
	void renderMenu();
	void renderGame();
	void renderDeath();
	void renderEnd();
public:
	GLFWwindow* window;

	GameComponents();
	
	void render();

	void end();
};


#endif