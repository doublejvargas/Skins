#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture(GLuint id);
	virtual ~Texture();

	inline GLuint ID() const { return m_TextureID;  };

private:
	GLuint m_TextureID;
};