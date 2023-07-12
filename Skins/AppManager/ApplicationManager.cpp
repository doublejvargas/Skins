#include <stdio.h>
#include <GL/glew.h>
#include <cstdlib>
#include <ctime>
#include "ApplicationManager.h"
#include "Render/OBJLoader.h"
#include "Render/Renderer.h"
#include "Toolbox/Math.h"
#include "Menu/MenuClearColor.h"
#include "Menu/SkinMenu.h"

ApplicationManager::ApplicationManager()
{
	if (glfwInit())
	{
		printf("GLFW initialized successfully \n");

		//Create Display Manager (don't forget to delete the pointer in destructor)
		m_DisplayManager = new DisplayManager(1280, 820, "Skins");

		//Initialize GLEW
		GLenum status = glewInit();
		if (status != GLEW_OK)
			printf("ERROR: GLEW failed to initialize \n%s", glewGetErrorString(status));
		else
		{
			printf("GLEW initialized successfully\n");
			m_DisplayManager->initializeImGui(); // initialize ImGUI after GLFW and GLEW.
		}

		printf("OpenGL version: %s\n", glGetString(GL_VERSION));	// print opengl version
	}
	else
	{
		printf("GLFW failed to initialize\n");
	}
}

ApplicationManager::~ApplicationManager()
{
	// Delete the display and clean up GLFW
	delete m_DisplayManager;
	glfwTerminate();
}

void ApplicationManager::Start()
{
	std::cout << __cplusplus << '\n';
	//Loader loader;

	//BasicShader shader("BasicShader");

	//Renderer renderer(shader, m_DisplayManager->GetAspectRatio());

	//std::string object = "res/models/dragon.obj";
	//RawModel frame = OBJLoader::LoadObjModel(object, loader);
	//Texture texture(loader.LoadTexture("res/textures/dragon.png"));
	//TexturedModel model(frame, texture);
	///*texture.SetShineDamper(10);
	//texture.SetReflectivity(1);
	//TexturedModel model(frame, texture);

	//Entity entity(model, glm::vec3(0, 0, -20), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));*/

	//Light light(glm::vec3(3000, 2000, 3000), glm::vec3(1, 1, 1));

	//Camera camera;

	//srand(time(0));
	//std::vector<Entity> entities;
	//for (int i = 0; i < 1; i++)
	//{
	//	int x = rand() % 200;
	//	int y = rand() % 200 - 50;
	//	int z = rand() % 200 - 200;
	//	entities.push_back(Entity(model, glm::vec3(x, y, z), glm::vec3(rand() * 180.0f, rand() * 90.0f, rand() * 45.0f), glm::vec3(1, 1, 1)));
	//}

	float n = 0.005f;

	printf("Running game loop...\n");

	glm::vec3 translation(0, 0, 0);
	
	double prevTime = glfwGetTime();
	int frameCount = 0;

	menu::Menu* currentMenu = nullptr;
	menu::MainMenu* mainMenu = new menu::MainMenu(currentMenu);
	currentMenu = mainMenu;

	//mainMenu->RegisterMenu<menu::MenuClearColor>("Clear Color");
	mainMenu->RegisterMenu<menu::SkinMenu>("ELDERFLAME", "res/models/AK_ELDERFLAME.obj", "res/textures/AK_ELDERFLAME.png");
	mainMenu->RegisterMenu<menu::SkinMenu>("ORIGIN", "res/models/AK_ORIGIN.obj", "res/textures/AK_ORIGIN.png");
	mainMenu->RegisterMenu<menu::SkinMenu>("ION", "res/models/AK_ION.obj", "res/textures/AK_ION.png");
	mainMenu->RegisterMenu<menu::SkinMenu>("ONI", "res/models/AK_ONI.obj", "res/textures/AK_ONI.png");
	mainMenu->RegisterMenu<menu::SkinMenu>("RUIN", "res/models/AK_RUIN.obj", "res/textures/AK_RUIN.png");
	mainMenu->RegisterMenu<menu::SkinMenu>("CHRONO", "res/models/AK_CHRONO.obj", "res/textures/AK_CHRONO.png");

	while (m_DisplayManager->IsWindowOpen())
	{

		DisplayManager::ImGuiNewFrame();
		if (currentMenu)
		{
			currentMenu->Clear();
			currentMenu->OnUpdate(0.0f);
			currentMenu->OnRender();
			
			//Default position and size of menu on first run of application.
			const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 83, main_viewport->WorkPos.y + 535), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(1100, 250), ImGuiCond_FirstUseEver);
			
			ImGui::Begin("Weapons");
			if (currentMenu != mainMenu && ImGui::Button("<-"))
			{
				delete currentMenu;
				currentMenu = mainMenu;
			}
			currentMenu->OnImGuiRender();
			ImGui::End();
		}

		DisplayManager::ImGuiFrameRender();

		m_DisplayManager->UpdateDisplay();
		m_DisplayManager->ShowFPS(prevTime, frameCount);
	}

	delete currentMenu;
	if (currentMenu != mainMenu)
		delete mainMenu;
}
