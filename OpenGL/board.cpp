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

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    fontLarger = io.Fonts->AddFontFromFileTTF("resources/fonts/smoochSans.ttf", 72.0f);
    fontSmaller = io.Fonts->AddFontFromFileTTF("resources/fonts/smoochSans.ttf", 32.0f);
	ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    mainMenu = Texture("resources/textures/flop.png", "None",1);

}

void GameComponents::render()
{
    if (mode == 0)
        this->renderMenu();
    else if (mode == 1)
        this->renderGame();
    else if (mode == 2)
        this->renderDeath();
    else
        this->renderEnd();
}

void GameComponents::renderMenu()
{
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
    window_flags |= ImGuiWindowFlags_NoResize;


    ImGui::Begin("Menu Glowne", (bool*)0, window_flags);
    ImGui::SetWindowPos(ImVec2(((float)WINDOW_WIDTH- WINDOW_HEIGHT)/2, (float)0));
    ImGui::SetWindowSize(ImVec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
    ImGui::Image((ImTextureID)(intptr_t)1, ImVec2(WINDOW_HEIGHT, WINDOW_HEIGHT));
    static bool clicked = false;
    ImGui::SetCursorScreenPos(ImVec2(WINDOW_WIDTH/2-200, WINDOW_HEIGHT*3/4));
    
    
    if (ImGui::Button("- Start -", ImVec2(400, 100)))
        clicked= true;

    if (clicked)
    {
        mainLocation = new Room(glm::vec3(0, -0.3, 0), glm::vec3(4.0, 1.0, 4.0), &importer, &phys, window);
        this->mode = 1;
    }
    
    ImGui::End();

    ImGui::Render();

    glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void GameComponents::renderEnd()
{

}
void GameComponents::renderDeath()
{

}
void GameComponents::renderGame()
{
    if (!paused)
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    glfwPollEvents();
    glfwGetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
    if (REMEMBERED_WIDTH != WINDOW_WIDTH || REMEMBERED_HEIGHT != WINDOW_HEIGHT)
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    REMEMBERED_WIDTH = WINDOW_WIDTH; 
    REMEMBERED_HEIGHT = WINDOW_HEIGHT;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !escPressed)
    {
        paused = !paused;
        escPressed = true;
    }
        
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && escPressed)
        escPressed = false;
    static float f = 0.0f;
    static int counter = 0;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoResize;
    ImGui::Begin("¯ycie Gracza",(bool*)0,window_flags);
    ImGui::PushFont(fontSmaller);
    ImGui::SetWindowPos(ImVec2((float)30, (float)30));
    ImGui::SetWindowSize(ImVec2((float)500, (float)100));
    ImGui::ProgressBar(this->mainLocation->getLifeBarFromPlayer(), ImVec2(0.0f, 0.0f));
    ImGui::PopFont();
    ImGui::End();
    ImGui::SetNextWindowBgAlpha(0.3);
    if (paused)
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoResize;
        ImGui::Begin("Menu W Grze", (bool*)0, window_flags);
        
        ImGui::SetWindowPos(ImVec2((float)0, (float)0));
        ImGui::SetWindowSize(ImVec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
        ImGui::SetCursorScreenPos(ImVec2(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT * 1 / 4));
        if (ImGui::Button("- Powrot do gry -", ImVec2(400, 100)))
            paused = false;

        ImGui::End();
    }


    ImGui::Render();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (!paused)
    {
        phys.process(fpsTime);
        camera.update(45.f, 0.1f, 100.0f);
        mainLocation->process(fpsTime, camera, false);
    }
    else
    {
        mainLocation->process(0, camera, true);
    }


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