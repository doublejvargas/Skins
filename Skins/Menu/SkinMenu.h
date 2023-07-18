#pragma once
#include<memory>
#include "Menu.h"

namespace menu
{
	class SkinMenu : public Menu
	{
	public:
		SkinMenu(const std::string& modelpath, const std::string& texturepath);
		~SkinMenu();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	
	private:
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

		glm::vec3 m_Translation;
	};
}