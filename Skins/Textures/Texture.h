#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture(GLuint id);
	virtual ~Texture();

	GLuint ID() const;

private:
	GLuint m_TextureID;
};