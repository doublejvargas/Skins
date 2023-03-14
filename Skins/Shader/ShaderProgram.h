#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& fileName);
	virtual ~ShaderProgram();

	void Bind() const;
	void Unbind() const;
	GLuint ProgramID() { return m_ProgramID; }

private:
	GLuint m_ProgramID;
	GLuint m_VertexShaderID;
	GLuint m_FragmentShaderID;
	std::unordered_map<std::string, int> m_UniformLocationCache; // local uniform location cache for better performance.

	GLuint LoadShader(const std::string& filename, GLenum type);

protected:
	virtual void BindAttributes();
	void BindAttribute(unsigned int layout_location, const std::string& name);
	
	virtual void GetAllUniformLocations();

	GLuint GetUniformLocation(const std::string& name);
	void SetUniform1f(GLuint location, float value);
	void SetUniformVec3f(GLuint location, const glm::vec3& value);
	void SetUniformBool(GLuint location, bool value);
	void SetUniformMat4f(GLuint location, const glm::mat4& matrix);
	//void SetUniform1iv(GLuint location, int count, const int* value);
};
