#include "BasicShader.h"


BasicShader::BasicShader(const std::string& filename)
	: ShaderProgram("res/shaders/" + filename), m_FilePath("res/shaders/" + filename) // parent class constructor
{
	BindAttributes();
	GetAllUniformLocations();
}

BasicShader::~BasicShader()
{
}


void BasicShader::LoadTransformMatrix(const glm::mat4& matrix)
{
	SetUniformMat4f("u_TransformMatrix", matrix);
}

void BasicShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	SetUniformMat4f("u_ProjectionMatrix", matrix);
}

void BasicShader::LoadViewMatrix(const glm::mat4& matrix)
{
	SetUniformMat4f("u_ViewMatrix", matrix);
}

void BasicShader::BindAttributes()
{
	BindAttribute(0, "a_Position");
	BindAttribute(1, "a_TexCoord");
}

void BasicShader::GetAllUniformLocations()
{
	m_TransformMatrixLoc = GetUniformLocation("u_TransformMatrix"); // ? don't understand this
	m_ProjectionMatrixLoc = GetUniformLocation("u_ProjectionMatrix");
	m_ViewMatrixLoc = GetUniformLocation("u_ViewMatrix");
}
