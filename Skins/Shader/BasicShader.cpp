#include "BasicShader.h"
#include "Toolbox/Math.h"

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
	SetUniformMat4f(m_TransformMatrixLoc, matrix);
}

void BasicShader::LoadProjectionMatrix(const glm::mat4& matrix)
{
	SetUniformMat4f(m_ProjectionMatrixLoc, matrix);
}

void BasicShader::LoadViewMatrix(Camera& camera)
{
	SetUniformMat4f(m_ViewMatrixLoc, Math::CreateViewMatrix(camera));
}

void BasicShader::LoadLight(Light& light, float ambientLight)
{
	SetUniformVec3f(m_LightPosLoc, light.Position());
	SetUniformVec3f(m_LightColLoc, light.Color());
	SetUniform1f(m_AmbientLightLoc, ambientLight);
}

void BasicShader::LoadShineVariables(float shinedamper, float reflectivity)
{
	SetUniform1f(m_ShineDamperLoc, shinedamper);
	SetUniform1f(m_ReflectivityLoc, reflectivity);
}

void BasicShader::BindAttributes()
{
	BindAttribute(0, "a_Position");
	BindAttribute(1, "a_TexCoord");
	BindAttribute(2, "a_NormalVector");
}

void BasicShader::GetAllUniformLocations()
{
	m_TransformMatrixLoc = GetUniformLocation("u_TransformMatrix"); // ? don't understand this
	m_ProjectionMatrixLoc = GetUniformLocation("u_ProjectionMatrix");
	m_ViewMatrixLoc = GetUniformLocation("u_ViewMatrix");
	m_LightPosLoc = GetUniformLocation("u_LightPosition");
	m_LightColLoc = GetUniformLocation("u_LightColor");
	m_AmbientLightLoc = GetUniformLocation("u_AmbientLight");
	m_ShineDamperLoc = GetUniformLocation("u_ShineDamper");
	m_ReflectivityLoc = GetUniformLocation("u_Reflectivity");
}
