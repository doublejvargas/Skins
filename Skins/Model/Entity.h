#pragma once

#include <glm\glm.hpp>
#include "TexturedModel.h"

class Entity
{
public:
	Entity(const TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: m_Model(model), m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

	inline void ChangePosition(const glm::vec3& position) { m_Position += position; }
	inline void ChangeRotation(const glm::vec3& rotation) { m_Rotation += rotation; }
	inline void ChangeScale(const glm::vec3& scale) { m_Scale += scale; }

	inline TexturedModel GetModel() { return m_Model; }
	inline glm::vec3 GetPosition() { return m_Position; }
	inline glm::vec3 GetRotation() { return m_Rotation; }
	inline glm::vec3 GetScale() { return m_Scale; }

	inline void SetModel(const TexturedModel& model) { m_Model = model; }
	inline void SetPosition(const glm::vec3& position) { m_Position = position; }
	inline void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
	inline void SetScale(const glm::vec3& scale) { m_Scale = scale; }

private:
	TexturedModel m_Model;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};
