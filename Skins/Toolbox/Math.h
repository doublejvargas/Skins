#pragma once

#include <glm/glm.hpp>
#include "Controller/Camera.h"

class Math
{
public:
	static glm::mat4 CreateTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
	static glm::mat4 CreateViewMatrix(Camera& camera);
};
