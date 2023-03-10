#include <iostream>
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
		std::cout << "GLFW initialized successfully" << std::endl;

		//Create Display Manager (don't forget to delete the pointer in destructor)
		m_DisplayManager = new DisplayManager(1280, 820, "Skins");

		//Initialize GLEW
		GLenum status = glewInit();
		if (status != GLEW_OK)
			std::cerr << "ERROR: GLEW failed to initialize \n" << glewGetErrorString(status) << std::endl;
		else
			std::cout << "GLEW initialized successfully" << std::endl;

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; // print opengl version
	}
	else
	{
		std::cerr << "GLFW failed to initialize" << std::endl;
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
	std::cout << "Running game loop..." << std::endl;
	
	double prevTime = glfwGetTime();
	int frameCount = 0;
	while (m_DisplayManager->IsWindowOpen())
	{
		//entity.ChangeRotation(glm::vec3(n, n, n));
		camera.Move();
		renderer.Clear();
		shader.Bind();
		shader.LoadViewMatrix(camera);
		shader.LoadLight(light);
		/*renderer.Render(entity, shader);*/
		for (Entity& e : entities)
		{
			renderer.Render(e, shader);
		}
		shader.Unbind();

		m_DisplayManager->UpdateDisplay();
		m_DisplayManager->ShowFPS(prevTime, frameCount);
	}
}
