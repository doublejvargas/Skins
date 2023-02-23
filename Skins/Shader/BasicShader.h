#pragma once

#include <string>
#include "ShaderProgram.h"

class BasicShader : public ShaderProgram
{
public:
	BasicShader(const std::string& filename);
	virtual ~BasicShader();

	void LoadTransformMatrix(const glm::mat4& matrix);
	void LoadProjectionMatrix(const glm::mat4& matrix);
	void LoadViewMatrix(const glm::mat4& matrix);

private:
	const std::string m_FilePath;
	GLuint m_TransformMatrixLoc; // also known as "model matrix"
	GLuint m_ProjectionMatrixLoc;
	GLuint m_ViewMatrixLoc;

protected:
	void BindAttributes() override;
	void GetAllUniformLocations() override;
};
