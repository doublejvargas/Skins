#include <iostream>
#include "DisplayManager.h"


DisplayManager::DisplayManager(int width /*= 1280*/, int height /*= 720*/, const std::string& title /*= "OpenGL Window"*/)
{
	// Create window using GLFW
	m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	
	if (m_Window != NULL)
	{
		// Set OpenGL context to the window
		glfwMakeContextCurrent(m_Window);
		// Set OpenGL viewport to window's full size
		glViewport(0, 0, width, height);
		// Enable Vsync
		glfwSwapInterval(1);
	}

	else
		std::cerr << "ERROR: Failed to create window" << std::endl;

}

DisplayManager::~DisplayManager()
{
	glfwDestroyWindow(m_Window);
}

bool DisplayManager::IsWindowOpen()
{
	return !glfwWindowShouldClose(m_Window);
}

void DisplayManager::UpdateDisplay()
{
	// tell GLFW to get window events
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}
