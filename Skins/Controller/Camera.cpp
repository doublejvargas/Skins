#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(const glm::vec3& pos, float yaw, float pitch)
	: m_Position(pos), m_Pitch(pitch), m_Yaw(yaw), m_Roll(0.0f) 
{
}

Camera::~Camera()
{
}

void Camera::Move()
{

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		m_Position.y += SPEED;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		m_Position.y -= SPEED;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		m_Position.x -= SPEED;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		m_Position.x += SPEED;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_Q) == GLFW_PRESS)
		m_Position.z -= SPEED;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
		m_Position.z += SPEED;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R) == GLFW_PRESS)
	{
		m_Position = glm::vec3(0, 0, 1.5f);
		m_Pitch = 0.0f;
		m_Yaw = -90.0f;
		m_Roll = 0.0f;
	}
}

