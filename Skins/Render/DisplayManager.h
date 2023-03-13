#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class DisplayManager
{

public:
	DisplayManager(int width = 1280, int height = 720, const std::string& title = "OpenGL Window");
	virtual ~DisplayManager();

	bool IsWindowOpen() const;
	void UpdateDisplay() const;
	inline float GetAspectRatio() const { return m_AspectRatio; }
	void ShowFPS(double& prevTime, int& frameCount);

	static void ImGuiNewFrame();
	static void ImGuiFrameRender();

private:
	GLFWwindow* m_Window;
	float m_AspectRatio;
	std::string m_Title;
};