#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class DisplayManager
{

public:
	static const float WIN_WIDTH;
	static const float WIN_HEIGHT;
	static const float WIN_ASPECT_RATIO;

	DisplayManager(int width = WIN_WIDTH, int height = WIN_HEIGHT, const std::string& title = "OpenGL Window");
	virtual ~DisplayManager();

	bool IsWindowOpen() const;
	void UpdateDisplay() const;

	inline float GetAspectRatio() const { return m_AspectRatio; }
	inline GLFWwindow* GetWindow() const { return m_Window; }

	void ShowFPS(double& prevTime, int& frameCount);

	void initializeImGui();

	static void ImGuiNewFrame();
	static void ImGuiFrameRender();

private:
	GLFWwindow* m_Window;
	float m_AspectRatio;
	std::string m_Title;

};