#include "Menu.h"
#include "imgui/imgui.h"
#include "Log.h"
#include "Render/OBJLoader.h"
#include "Render/DisplayManager.h"

namespace menu
{

	MainMenu::MainMenu(Menu*& currentMenuPointer)
		: m_CurrentMenu(currentMenuPointer)
	{
		m_Light = std::make_unique<Light>(glm::vec3(700, 500, 700), glm::vec3(1, 1, 1));
		m_Camera = std::make_unique<Camera>(glm::vec3(0, 0, 1.5f));
		m_Shader = std::make_unique<BasicShader>("BasicShader");
		m_TerrainShader = std::make_unique<BasicShader>("BasicTerrainShader");
		m_Renderer = std::make_unique<Renderer>(*m_Shader, DisplayManager::WIN_ASPECT_RATIO);
		m_TerrainRenderer = std::make_unique<TerrainRenderer>(*m_TerrainShader, DisplayManager::WIN_ASPECT_RATIO);

		m_Loader = std::make_unique<Loader>(); // don't destroy this!! otherwise, will destroy all vaos, vbos, ibos and textures...

		m_RawModel = std::make_unique<RawModel>(OBJLoader::LoadObjModel("res/models/AK_DEFAULT.obj", *m_Loader));
		m_Texture = std::make_unique<Texture>(m_Loader->LoadTexture("res/textures/AK_DEFAULT.png"));
		m_Texture->SetShineDamper(10);
		m_Texture->SetReflectivity(1);
		m_TexturedModel = std::make_unique<TexturedModel>(*m_RawModel, *m_Texture);

		m_Terrain = std::make_unique<Terrain>(0, 0, m_Loader.get(), Texture(m_Loader->LoadTexture("res/textures/others/grass.png")));

		m_Entities = std::make_unique<std::vector<Entity>>(3);
		m_Entities->at(0) = Entity(*m_TexturedModel);
		m_Entities->at(1) = Entity(TexturedModel(m_Terrain->getRawModel(), m_Terrain->getTexture()), glm::vec3(-500.0f, -2.0f, -500.0f));
		m_Entities->at(2) = Entity(TexturedModel(m_Terrain->getRawModel(), m_Terrain->getTexture()), glm::vec3(0, -2.0f, -500.0f));
	}

	void MainMenu::OnUpdate(float deltaTime)
	{
		float n = 0.005f;
		m_Entities->at(0).ChangeRotation(glm::vec3(0, n, 0));
		m_Camera->Move();
	}

	void MainMenu::OnRender()
	{
		m_Renderer->Clear();
		m_TerrainRenderer->Clear();

		m_Shader->Bind();
		m_Shader->LoadViewMatrix(*m_Camera);
		m_Shader->LoadLight(*m_Light, 0.15f);
		m_Renderer->Render(m_Entities->at(0), *m_Shader);
		m_Shader->Unbind();

		m_TerrainShader->Bind();
		m_TerrainShader->LoadViewMatrix(*m_Camera);
		m_TerrainShader->LoadLight(*m_Light, 0.15f);
		m_TerrainRenderer->Render(m_Entities->at(1), *m_TerrainShader);
		m_TerrainRenderer->Render(m_Entities->at(2), *m_TerrainShader);
		m_TerrainShader->Unbind();		
	}

	void MainMenu::OnImGuiRender()
	{
		ImGui::Columns(2);
		for (auto& menu : m_Menus)
		{
			if (ImGui::Button(menu.first.c_str(), { 128, 64 }))
			{
				m_CurrentMenu = menu.second();
			}
			ImGui::NextColumn();
		}

		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	void Menu::Clear()
	{
		//GLCall(glClearColor(0.1f, 0.2f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

}