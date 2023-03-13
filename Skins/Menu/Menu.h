#pragma once

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
}