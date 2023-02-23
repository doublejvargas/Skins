#pragma once

//#include "Model/RawModel.h" //includes GL/glew.h
#include "Model/TexturedModel.h" // includes rawmodel which also includes GL/glew
#include "Model/Entity.h"
#include "Shader/BasicShader.h"

static const float FOV = 70;
static const float NEAR_PLANE = 0.1f;
static const float FAR_PLANE = 1000.0f;

class Renderer
{
public:

	Renderer(BasicShader& shader, const float& aspect);
	virtual ~Renderer();

	void Clear() const;
	void Render(Entity& entity, BasicShader& shader);

private:
	glm::mat4 m_ProjectionMatrix;
};