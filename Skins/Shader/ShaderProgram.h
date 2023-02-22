#pragma once

#include <string>
#include <GL/glew.h>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& fileName);
	virtual ~ShaderProgram();

	void Bind();
	void Unbind();
	GLuint ProgramID() { return m_ProgramID; }

private:
	GLuint m_ProgramID;
	GLuint m_VertexShaderID;
	GLuint m_FragmentShaderID;

	GLuint LoadShader(const std::string& filename, GLenum type);

protected:
	virtual void BindAttributes() = 0; // pure virtual function
	void BindAttribute(unsigned int layout_location, const std::string& name);
};
