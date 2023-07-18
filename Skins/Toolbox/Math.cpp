#include "Math.h"
#include "glm/gtc/matrix_transform.hpp"

glm::vec3 cameraFront = glm::vec3(0, 0, -1);
const glm::vec3 worldUp = glm::vec3(0, 1, 0);
glm::vec3 cameraUp;
glm::vec3 cameraRight;

glm::mat4 Math::CreateTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
	// create translation matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
	// create rotation matrix
	glm::mat4 rotationMatrix =
		glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1, 0, 0));
	// create scale matrix
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	// the transformation matrix is the product of the three
	return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 Math::CreateViewMatrix(Camera& camera)
{
	glm::vec3 front;
	front.x = glm::cos(glm::radians(camera.GetYaw())) * glm::cos(glm::radians(camera.GetPitch()));
	front.y = glm::sin(glm::radians(camera.GetPitch()));
	front.z = glm::sin(glm::radians(camera.GetYaw())) * glm::cos(glm::radians(camera.GetPitch()));
	cameraFront = glm::normalize(front);

	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));

	return glm::lookAt(camera.GetPosition(), camera.GetPosition() + cameraFront, cameraUp);
}

