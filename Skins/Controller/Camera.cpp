#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera()
	: m_Position(glm::vec3(0, 0, 40)), m_Pitch(0.0f), m_Yaw(0.0f), m_Roll(0.0f)
{
}

Camera::~Camera()
{
}

void Camera::Move()
{
	float sens = 0.8f;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		m_Position.y += sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		m_Position.y -= sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		m_Position.x -= sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		m_Position.x += sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_Q) == GLFW_PRESS)
		m_Position.z -= sens;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
		m_Position.z += sens;
}

