#pragma once

#include <glm/glm.hpp>

const float YAW			= -90.0f;
const float PITCH		= 0.0f;
const float SPEED		= 0.05f;
const float SENSITIVITY = 0.1f;
const float ZOOM		= 45.0f;

class Camera
{
public:
	Camera(const glm::vec3& pos = glm::vec3(0, 0, 2), float yaw = YAW, float pitch = PITCH);
	virtual ~Camera();

	void Move();

	inline glm::vec3 GetPosition() const	{ return m_Position; }
	inline float GetPitch() const			{ return m_Pitch; }
	inline float GetYaw() const				{ return m_Yaw; }
	inline float GetRoll() const			{ return m_Roll; }

	inline void SetPitch(float theta)		{ m_Pitch = theta; }
	inline void SetYaw(float theta)			{ m_Yaw = theta; }
	inline void SetRoll(float theta)		{ m_Roll = theta; }
private:
	glm::vec3 m_Position;
	// Angles in float degrees
	float m_Pitch, m_Yaw, m_Roll;

};
