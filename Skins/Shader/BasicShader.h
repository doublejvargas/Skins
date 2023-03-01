#pragma once

#include <string>
#include "ShaderProgram.h"
#include "Controller/Camera.h"
#include "Shader/Light.h"

class BasicShader : public ShaderProgram
{
public:
	BasicShader(const std::string& filename);
	virtual ~BasicShader();

	void LoadTransformMatrix(const glm::mat4& matrix);
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera);
	void LoadLight(Light light);

private:
	const std::string m_FilePath;
	GLuint m_TransformMatrixLoc; // also known as "model matrix"
	GLuint m_ProjectionMatrixLoc;
	GLuint m_ViewMatrixLoc;
	GLuint m_LightPosLoc;
	GLuint m_LightColLoc;

protected:
	void BindAttributes() override;
	void GetAllUniformLocations() override;
};
