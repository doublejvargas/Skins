#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include "Render/Renderer.h"
#include "Render/Loader.h"
#include "Model/Terrain.h"
#include "Render/TerrainRenderer.h"

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

		void Clear();

	};

	class MainMenu : public Menu
	{
	public:
		MainMenu(Menu*& currentMenuPointer);

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		template<typename T>
		void RegisterMenu(const std::string& name, const std::string& modelpath, const std::string& texturepath)
		{
			std::cout << "Registering test " << name << std::endl;
			m_Menus.push_back(std::make_pair(name, [&, modelpath, texturepath]() { return new T(modelpath, texturepath); }));
		}

	private:
		Menu*& m_CurrentMenu;
		std::vector < std::pair<std::string, std::function<Menu* ()>> >  m_Menus;

		std::unique_ptr<RawModel> m_RawModel;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<TexturedModel> m_TexturedModel;
		std::unique_ptr<std::vector<Entity>> m_Entities;

		std::unique_ptr<Terrain> m_Terrain;

		std::unique_ptr<BasicShader> m_Shader;
		std::unique_ptr<BasicShader> m_TerrainShader;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<TerrainRenderer> m_TerrainRenderer;
		std::unique_ptr<Light> m_Light;
		std::unique_ptr<Camera> m_Camera;

		std::unique_ptr<Loader> m_Loader;
	};
}