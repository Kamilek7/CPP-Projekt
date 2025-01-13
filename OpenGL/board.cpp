#include "board.h"


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

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    camera = Camera(&WINDOW_WIDTH, &WINDOW_HEIGHT, glm::vec3(0.0f, 0.2f, 0.5f));

    mainLocation = new Room(glm::vec3(0, -0.3, 0), glm::vec3(4.0, 1.0, 4.0), &importer, &phys, window);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
}

void GameComponents::render()
{
    glfwPollEvents();
    glfwGetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
    if (REMEMBERED_WIDTH != WINDOW_WIDTH || REMEMBERED_HEIGHT != WINDOW_HEIGHT)
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    REMEMBERED_WIDTH = WINDOW_WIDTH; 
    REMEMBERED_HEIGHT = WINDOW_HEIGHT;


    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    phys.process(fpsTime);
    camera.update(45.f, 0.1f, 100.0f);
    mainLocation->process(fpsTime, camera);


    // Ograniczenie FPS
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
    /*mainLocation.shaderProgram.remove();*/
    delete mainLocation;
    glfwDestroyWindow(window);
    glfwTerminate();
}
