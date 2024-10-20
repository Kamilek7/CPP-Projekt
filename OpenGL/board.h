#ifndef BOARD_H
#define BOARD_H
	
#include"grounds.h"
#include"physicsObject.h"

class GameComponents
{
	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 800;
	unsigned int MAX_FPS = 120;
	double fpsTime = 1 / double(MAX_FPS);
	modelImporter importer;
	Shader shaderProgram;
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.1f, 1.0f, 0.5f);
	Camera camera;
	std::vector <ingameObject*> objects;

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