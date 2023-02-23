#include "Entity.h"

Entity::Entity(const TexturedModel& model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: m_Model(model), m_Position(position), m_Rotation(rotation), m_Scale(scale)
{
}

Entity::~Entity()
{
}

void Entity::ChangePosition(const glm::vec3& position)
{
	m_Position += position;
}

void Entity::ChangeRotation(const glm::vec3& rotation)
{
	m_Rotation += rotation;
}

void Entity::ChangeScale(const glm::vec3& scale)
{
	m_Scale += scale;
}

