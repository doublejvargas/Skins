#pragma once

#include <string>
#include "ShaderProgram.h"

class BasicShader : public ShaderProgram
{
public:
	BasicShader(const std::string& filename);
	virtual ~BasicShader();

private:
	const std::string m_FilePath;

protected:
	void BindAttributes() override;
};
