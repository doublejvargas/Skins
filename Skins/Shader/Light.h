#pragma once

#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 pos, glm::vec3 col) : m_Position(pos), m_Color(col) {}

	inline glm::vec3 Position() { return m_Position; }
	inline glm::vec3 Color() { return m_Color; }
	inline void SetColor(glm::vec3 col) { m_Color = col; }

private:
	glm::vec3 m_Position, m_Color;
};