#include "SkinMenu.h"
//#include "Log.h"
#include "imgui/imgui.h"
#include "Render/OBJLoader.h"

namespace menu {

	SkinMenu::SkinMenu(const std::string& modelpath, const std::string& texturepath)
	{


		m_Light = std::make_unique<Light>(glm::vec3(700, 500, 700), glm::vec3(1, 1, 1));
		m_Camera = std::make_unique<Camera>(glm::vec3(0, 0, 2));
		m_Shader = std::make_unique<BasicShader>("BasicShader");
		m_Renderer = std::make_unique<Renderer>(*m_Shader, 1280.0f / 720.0f);

		m_Translation = glm::vec3(0, 0, 0);

		m_Loader = std::make_unique<Loader>(); // don't destroy this!! otherwise, will destroy all vaos, vbos, ibos and textures...

		m_RawModel = std::make_unique<RawModel>(OBJLoader::LoadObjModel(modelpath, *m_Loader));
		m_Texture = std::make_unique<Texture>(m_Loader->LoadTexture(texturepath));
		m_Texture->SetShineDamper(10);
		m_Texture->SetReflectivity(1);
		m_TexturedModel = std::make_unique<TexturedModel>(*m_RawModel, *m_Texture);

		m_Entity = std::make_unique<Entity>(*m_TexturedModel, glm::vec3(0, 0, -20), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	}

	SkinMenu::~SkinMenu()
	{
	}

	void SkinMenu::OnUpdate(float deltaTime)
	{
		float n = 0.005f;
		m_Entity->ChangeRotation(glm::vec3(0, n, 0));
		m_Camera->Move();
		m_Entity->SetPosition(m_Translation);
	}

	void SkinMenu::OnRender()
	{
		m_Renderer->Clear();
		m_Shader->Bind();

		m_Shader->LoadViewMatrix(*m_Camera);
		m_Shader->LoadLight(*m_Light, 0.15f);

		m_Renderer->Render(*m_Entity, *m_Shader);
		
		m_Shader->Unbind();
	}

	void SkinMenu::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation", &m_Translation.x, -5.0f, 5.0f);
		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}

