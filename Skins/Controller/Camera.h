#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void Move();

	inline glm::vec3 GetPosition() { return m_Position; }
	inline float GetPitch() { return m_Pitch; }
	inline float GetYaw() { return m_Yaw; }
	inline float GetRoll() { return m_Roll; }
private:
	glm::vec3 m_Position;
	// Angles in float radians
	float m_Pitch, m_Yaw, m_Roll;

};
