#include <iostream>
#include <GL/glew.h>
#include "ApplicationManager.h"

ApplicationManager::ApplicationManager()
{
	if (glfwInit())
	{
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
		{
			std::cerr << "ERROR: GLEW failed to initialize \n" << glewGetErrorString(status) << std::endl;
		}
		std::cout << glGetString(GL_VERSION) << std::endl; // print opengl version
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
	while (m_DisplayManager->IsWindowOpen())
	{
		m_DisplayManager->UpdateDisplay();
	}
}
