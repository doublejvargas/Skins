#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture(GLuint id) : m_TextureID(id) {}
	Texture() : m_TextureID(0) {}

	inline GLuint ID() const { return m_TextureID;  }
	inline float GetShineDamper() { return m_ShineDamper; }
	inline float GetReflectivity() { return m_Reflectivity; }
	inline void SetShineDamper(float s) { m_ShineDamper = s; }
	inline void SetReflectivity(float r) { m_Reflectivity = r; }

private:
	GLuint m_TextureID;
	float m_ShineDamper = 1;
	float m_Reflectivity = 0;
};