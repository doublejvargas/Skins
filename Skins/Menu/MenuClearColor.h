#pragma once
#include "Menu.h"

namespace menu
{
	class MenuClearColor : public Menu
	{
	public:
		MenuClearColor();
		~MenuClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	
	private:
		float m_ClearColor[4];
	};
}