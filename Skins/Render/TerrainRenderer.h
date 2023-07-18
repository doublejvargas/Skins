#pragma once

#include "Model/Entity.h"
#include "Shader/BasicShader.h"

class TerrainRenderer
{
public:

	TerrainRenderer(BasicShader& shader, const float& aspect);
	virtual ~TerrainRenderer();

	void Clear() const;
	void Render(Entity& entity, BasicShader& shader);

private:
	glm::mat4 m_ProjectionMatrix;
};