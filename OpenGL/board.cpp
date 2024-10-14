#include "board.h"

GameComponents::GameComponents()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "sraka", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	shaderProgram = Shader("default.vert", "default.frag");
	shaderProgram.on();
	glUniform4f(glGetUniformLocation(shaderProgram.program, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.program, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.2f, 0.5f));
	objects.push_back(new ingameObject("resources/sbunny/scene.gltf", &importer));
	/*objects.push_back(new ingameObject("resources/bonetest/test.gltf", &importer));*/
}

void GameComponents::render()
{

	glfwPollEvents();
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.update(45.f, 0.1f, 100.0f);
	// fps limit
	while (duration <= fpsTime)
	{
		current = glfwGetTime();
		duration = current - previousTime;
	}
	duration = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->process(fpsTime, shaderProgram, camera);
	}
	camera.inputs(window, (float)fpsTime);
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