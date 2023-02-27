#include <iostream>
#include "DisplayManager.h"
#include <cmath> // round function

DisplayManager::DisplayManager(int width /*= 1280*/, int height /*= 720*/, const std::string& title /*= "OpenGL Window"*/)
{
	m_Title = title;
	m_AspectRatio = (float)width / (float)height;
	
	// Set minimum OpenGL version and options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Create window using GLFW
	m_Window = glfwCreateWindow(width, height, m_Title.c_str(), NULL, NULL);
	
	if (m_Window != NULL)
	{
		std::cout << "GLFW window created successfully" << std::endl;
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
	std::cout << "Window destroyed" << std::endl;
	glfwDestroyWindow(m_Window);
}

bool DisplayManager::IsWindowOpen() const
{
	return !glfwWindowShouldClose(m_Window);
}

void DisplayManager::UpdateDisplay() const
{
	// Tell GLFW to swap buffers
	glfwSwapBuffers(m_Window);
	// Tell GLFW to get window events
	glfwPollEvents();
}

void DisplayManager::ShowUPS()
{
	// Static variables are only initialized only once, ever
	// Used for the size of the average array
	const static int SIZE = 500;
	// Array used to store every frames render time
	static double avgList[SIZE] = { 0.0 };
	// Variables to compute frame render time
	static double previous = 0.0;
	double now = glfwGetTime();
	double average = 0.0;

	// Move every value in the list forward, value position 1 is now in position 0
	for (unsigned int i = 0; i < SIZE - 1; i++)
	{
		avgList[i] = avgList[i + 1];
		average += avgList[i];
	}
	// Store the new time in the last slot
	avgList[SIZE - 1] = now - previous;
	// Add the new time to the average
	average += avgList[SIZE - 1];
	// Divide average my the array size to get the average time
	average /= SIZE;

	// Update the title with the FPS
	glfwSetWindowTitle(m_Window, (m_Title + " | Updates per second: " + std::to_string((int)round(1.0f / average))).c_str());

	// Store the current time
	previous = now;
}
