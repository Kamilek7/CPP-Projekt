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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
    io.MouseDrawCursor = false;
	ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");


}

void GameComponents::render()
{
    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    glfwPollEvents();
    glfwGetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
    if (REMEMBERED_WIDTH != WINDOW_WIDTH || REMEMBERED_HEIGHT != WINDOW_HEIGHT)
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    REMEMBERED_WIDTH = WINDOW_WIDTH; 
    REMEMBERED_HEIGHT = WINDOW_HEIGHT;

    static float f = 0.0f;
    static int counter = 0;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoResize;
    ImGui::Begin("¯ycie gracza",(bool*)0,window_flags);
    ImGui::SetWindowSize(ImVec2((float)500, (float)100));
    ImGui::ProgressBar(this->mainLocation->getLifeBarFromPlayer(), ImVec2(0.0f, 0.0f));
    ImGui::End();

    ImGui::Render();

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
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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