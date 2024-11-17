#include "board.h"
#include <cstdlib>
#include <ctime>

GameComponents::GameComponents()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Engine Test", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	shaderProgram = Shader("default.vert", "default.frag");
	shaderProgram.on();
	glUniform4f(glGetUniformLocation(shaderProgram.program, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.program, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.2f, 0.5f));

	
	objects.push_back(new physicsObject("resources/agumon/Agumon.obj", &importer, &phys));
	objects.push_back(new physicsObject("resources/aquilamon/Aquilamon.obj", &importer, &phys));
	objects.push_back(new physicsObject("resources/blackAgumon/BlackAgumon.obj", &importer, &phys));
	objects.push_back(new physicsObject("resources/tanemon/Tanemon.obj", &importer, &phys));
	objects.push_back(new physicsObject("resources/tsunomon/Tsunomon.obj", &importer, &phys));
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->scaleBy(0.1);
	}
	objects.push_back(new Scientist( & importer, &phys));
	objects.push_back(new Basilisk(&importer, &phys));
	objects.push_back(new Fighter(&importer, &phys));

	objects.push_back(new physicsObject("resources/darkTyrannomon/DarkTyrannomon.obj", &importer, &phys));
	objects[objects.size()-1]->scaleBy(0.2);

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->translate(-0.8 + double(i * 0.6),0.2);
	}
	
	objects.push_back(new Grounds(&importer, &phys));
	objects[objects.size() - 1]->translate(0, -0.2, 0);

	objects.push_back(new Player(&importer, &phys,window));


}

void GameComponents::render()
{

	glfwPollEvents();
	glfwGetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	phys.process(fpsTime);
	camera.update(45.f, 0.1f, 100.0f);

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->process(fpsTime, shaderProgram, camera);
	}

	// fps limit
	while (duration <= fpsTime)
	{
		current = glfwGetTime();
		duration = current - previousTime;
	}

	duration = 0;
	Clock += (float)fpsTime;
	glfwSwapBuffers(window);
	previousTime = glfwGetTime();
}

void GameComponents::end()
{
	shaderProgram.remove();
	glfwDestroyWindow(window);
	glfwTerminate();
}