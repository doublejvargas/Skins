#include "Menu.h"
#include "imgui/imgui.h"
#include "Log.h"
#include "Render/OBJLoader.h"

namespace menu
{

	MainMenu::MainMenu(Menu*& currentMenuPointer)
		: m_CurrentMenu(currentMenuPointer)
	{
		m_Light = std::make_unique<Light>(glm::vec3(700, 500, 700), glm::vec3(1, 1, 1));
		m_Camera = std::make_unique<Camera>(glm::vec3(0, 0, 2));
		m_Shader = std::make_unique<BasicShader>("BasicShader");
		m_Renderer = std::make_unique<Renderer>(*m_Shader, 1280.0f / 720.0f);

		m_Translation = glm::vec3(0, 0, 0);

		m_Loader = std::make_unique<Loader>(); // don't destroy this!! otherwise, will destroy all vaos, vbos, ibos and textures...

		m_RawModel = std::make_unique<RawModel>(OBJLoader::LoadObjModel("res/models/AK_DEFAULT.obj", *m_Loader));
		m_Texture = std::make_unique<Texture>(m_Loader->LoadTexture("res/textures/AK_DEFAULT.png"));
		m_Texture->SetShineDamper(10);
		m_Texture->SetReflectivity(1);
		m_TexturedModel = std::make_unique<TexturedModel>(*m_RawModel, *m_Texture);

		m_Entity = std::make_unique<Entity>(*m_TexturedModel, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	}

	void MainMenu::OnUpdate(float deltaTime)
	{
		float n = 0.005f;
		m_Entity->ChangeRotation(glm::vec3(0, n, 0));
	}

	void MainMenu::OnRender()
	{
		m_Renderer->Clear();
		m_Shader->Bind();

		m_Shader->LoadViewMatrix(*m_Camera);
		m_Shader->LoadLight(*m_Light, 0.15f);

		m_Renderer->Render(*m_Entity, *m_Shader);

		m_Shader->Unbind();
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