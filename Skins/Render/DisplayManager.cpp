#include <iostream>
#include "DisplayManager.h"


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
	// Cleanup ImGUI
	std::cout << "Shutting down ImGui" << std::endl;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Cleanup GLFW
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

void DisplayManager::ShowFPS(double& prevTime, int& frameCount)
{
	double currentTime = glfwGetTime();
	frameCount++;
	if (currentTime - prevTime >= 1.0)
	{
		glfwSetWindowTitle(m_Window, (m_Title + " | FPS: " + std::to_string(frameCount)).c_str());
		frameCount = 0;
		prevTime = currentTime;
	}
}

void DisplayManager::ImGuiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void DisplayManager::ImGuiFrameRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DisplayManager::initializeImGui()
{
	const char* glsl_version = "#version 330 core";
	// Initialize ImGUI
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	std::cout << "imgui initialized??" << std::endl;
}
