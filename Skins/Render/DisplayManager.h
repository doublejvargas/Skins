#pragma once
#include <string>
#include <GLFW/glfw3.h>

class DisplayManager
{

public:
	DisplayManager(int width = 1280, int height = 720, const std::string& title = "OpenGL Window");
	virtual ~DisplayManager();

	bool IsWindowOpen() const;
	void UpdateDisplay() const;

private:
	GLFWwindow* m_Window;

};