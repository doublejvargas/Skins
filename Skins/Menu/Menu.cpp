#include "Menu.h"
#include "imgui/imgui.h"
#include "Log.h"

namespace menu
{

	MainMenu::MainMenu(Menu*& currentMenuPointer)
		: m_CurrentMenu(currentMenuPointer)
	{
	}

	void MainMenu::OnImGuiRender()
	{

		for (auto& menu : m_Menus)
		{
			if (ImGui::Button(menu.first.c_str()))
				m_CurrentMenu = menu.second();
		}

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	void Menu::Clear()
	{
		GLCall(glClearColor(0.1f, 0.2f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

}