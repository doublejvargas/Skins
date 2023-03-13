#include <stdio.h>
#include <GL/glew.h>
#include <cstdlib>
#include <ctime>
#include "ApplicationManager.h"
#include "Render/OBJLoader.h"
#include "Render/Renderer.h"
#include "Model/TexturedModel.h"
#include "Shader/BasicShader.h"
#include "Toolbox/Math.h"
#include "Menu/MenuClearColor.h"

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
			printf("GLEW initialized successfully\n");

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
	Loader loader;

	BasicShader shader("BasicShader");

	Renderer renderer(shader, m_DisplayManager->GetAspectRatio());

	std::string object = "res/models/dragon.obj";
	RawModel frame = OBJLoader::LoadObjModel(object, loader);
	Texture texture(loader.LoadTexture("res/textures/dragon.png"));
	TexturedModel model(frame, texture);
	/*texture.SetShineDamper(10);
	texture.SetReflectivity(1);
	TexturedModel model(frame, texture);

	Entity entity(model, glm::vec3(0, 0, -20), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));*/

	Light light(glm::vec3(3000, 2000, 3000), glm::vec3(1, 1, 1));

	Camera camera;

	srand(time(0));
	std::vector<Entity> entities;
	for (int i = 0; i < 1; i++)
	{
		int x = rand() % 200;
		int y = rand() % 200 - 50;
		int z = rand() % 200 - 200;
		entities.push_back(Entity(model, glm::vec3(x, y, z), glm::vec3(rand() * 180.0f, rand() * 90.0f, rand() * 45.0f), glm::vec3(1, 1, 1)));
	}

	float n = 0.005f;

	printf("Running game loop...\n");

	glm::vec3 translation(0, 0, 0);
	
	double prevTime = glfwGetTime();
	int frameCount = 0;

	menu::MenuClearColor menu;
	while (m_DisplayManager->IsWindowOpen())
	{
		//entity.ChangeRotation(glm::vec3(n, n, n));
		//camera.Move();
		renderer.Clear();
		menu.OnUpdate(0.0f);
		menu.OnRender();
		//shader.Bind();

		DisplayManager::ImGuiNewFrame();

		//shader.LoadViewMatrix(camera);
		//shader.LoadLight(light, 0.15f);
		///*renderer.Render(entity, shader);*/
		//for (Entity& e : entities)
		//{
		//	renderer.Render(e, shader);
		//	{
		//		ImGui::Begin("Menu");
		//		ImGui::SliderFloat3("Translation", &translation.x, -50.0f, 50.0f);
		//		e.SetPosition(translation);
		//		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//		ImGui::End();
		//	}

		//}
		//shader.Unbind();

		menu.OnImGuiRender();

		DisplayManager::ImGuiFrameRender();

		m_DisplayManager->UpdateDisplay();
		m_DisplayManager->ShowFPS(prevTime, frameCount);
	}
}
