#include "BasicShader.h"


BasicShader::BasicShader(const std::string& filename)
	: ShaderProgram("res/shaders/" + filename), m_FilePath("res/shaders/" + filename) // parent class constructor
{
	this->Bind();
	BindAttributes();
}


BasicShader::~BasicShader()
{
}


void BasicShader::BindAttributes()
{
	BindAttribute(0, "a_Position");
}