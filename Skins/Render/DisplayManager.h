#pragma once
#include <string>
#include <GLFW/glfw3.h>

class DisplayManager
{

public:
	DisplayManager(int width = 1280, int height = 720, const std::string& title = "OpenGL Window");
	virtual ~DisplayManager();

	bool IsWindowOpen();
	void UpdateDisplay();

private:
	GLFWwindow* m_Window;

};