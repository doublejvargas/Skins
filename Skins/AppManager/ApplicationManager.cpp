#include <iostream>
#include <GL/glew.h>
#include "ApplicationManager.h"
#include "Render/Loader.h"
#include "Render/Renderer.h"
#include "Render/RawModel.h"

ApplicationManager::ApplicationManager()
{
	if (glfwInit())
	{
		std::cout << "GLFW initialized successfully" << std::endl;
		// Set minimum OpenGL version and options
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	delete m_DisplayManager;
	glfwTerminate();
}

void ApplicationManager::Start()
{
	Loader loader;
	Renderer renderer;

	float vertices[] = {
		-0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,

		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	RawModel model = loader.LoadToVAO(vertices, sizeof(vertices) / sizeof(vertices[0]));

	std::cout << "Running game loop..." << std::endl;
	while (m_DisplayManager->IsWindowOpen())
	{
		renderer.Prepare();
		renderer.Render(model);

		m_DisplayManager->UpdateDisplay();
	}
}
