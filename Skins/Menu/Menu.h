#pragma once
#include <functional>
#include <vector>
#include <iostream>

namespace menu
{
	class Menu
	{
	public:
		Menu() {}
		virtual ~Menu() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	};

	class MainMenu : public Menu
	{
	public:
		MainMenu(Menu*& currentMenuPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterMenu(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;
			m_Menus.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		Menu*& m_CurrentMenu;
		std::vector < std::pair<std::string, std::function<Menu* ()>> >  m_Menus;
	};
}