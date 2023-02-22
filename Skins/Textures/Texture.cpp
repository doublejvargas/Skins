#pragma once

#include "Texture.h"

Texture::Texture(GLuint id)
	: m_TextureID(id)
{
}

Texture::~Texture()
{
}

GLuint Texture::ID() const
{
	return m_TextureID;
}
