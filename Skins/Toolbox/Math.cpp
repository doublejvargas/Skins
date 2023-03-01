#include "Math.h"
#include "glm/gtc/matrix_transform.hpp"

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
	// camera is at (0, 0, 0) looking at objects INTO the screen (0, 0, -1)
	return glm::lookAt(camera.GetPosition(), camera.GetPosition() + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}

