#pragma once

#include <string>
#include "ShaderProgram.h"
#include "Controller/Camera.h"
#include "Shader/Light.h"

const float RED = 0.5f;
const float GREEN = 0.5f;
const float BLUE = 0.5f;

class BasicShader : public ShaderProgram
{
public:
	BasicShader(const std::string& filename);

	void LoadTransformMatrix(const glm::mat4& matrix);
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera);
	void LoadLight(Light& light, float ambientLight);
	void LoadShineVariables(float shinedamper, float reflectivity);
	void LoadSkyColor(const glm::vec3& rgb);

private:
	const std::string m_FilePath;

	// Uniform locations
	GLuint m_TransformMatrixLoc; // also known as "model matrix"
	GLuint m_ProjectionMatrixLoc;
	GLuint m_ViewMatrixLoc;
	GLuint m_LightPosLoc;
	GLuint m_LightColLoc;
	GLuint m_AmbientLightLoc;
	GLuint m_ShineDamperLoc;
	GLuint m_ReflectivityLoc;
	GLuint m_SkyColorLoc;
	

protected:
	void BindAttributes() override;
	void GetAllUniformLocations() override;
};
