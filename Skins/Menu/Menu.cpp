#include "Menu.h"
#include "imgui/imgui.h"

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
	}

}