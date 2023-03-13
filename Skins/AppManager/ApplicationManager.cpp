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
	for (int i = 0; i < 200; i++)
	{
		int x = rand() % 200;
		int y = rand() % 200 - 50;
		int z = rand() % 200 - 200;
		entities.push_back(Entity(model, glm::vec3(x, y, z), glm::vec3(rand() * 180.0f, rand() * 90.0f, rand() * 45.0f), glm::vec3(1, 1, 1)));
	}

	float n = 0.005f;

	// TODO: instead of implementing camera, modify it to implement a CONTROL class to move objects and view.
	printf("Running game loop...\n");

	// IMGUI state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	
	double prevTime = glfwGetTime();
	int frameCount = 0;
	while (m_DisplayManager->IsWindowOpen())
	{
		//entity.ChangeRotation(glm::vec3(n, n, n));
		camera.Move();
		renderer.Clear();
		shader.Bind();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		shader.LoadViewMatrix(camera);
		shader.LoadLight(light, 0.15f);
		/*renderer.Render(entity, shader);*/
		for (Entity& e : entities)
		{
			renderer.Render(e, shader);
		}
		shader.Unbind();

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		m_DisplayManager->UpdateDisplay();
		m_DisplayManager->ShowFPS(prevTime, frameCount);
	}
}
