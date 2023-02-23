#include "Renderer.h"
#include "Log.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Toolbox/Math.h"
#include "Model/TexturedModel.h"

Renderer::Renderer(BasicShader& shader, const float& aspect)
{
	m_ProjectionMatrix = glm::perspective(FOV, aspect, NEAR_PLANE, FAR_PLANE);

	shader.Bind();
	shader.LoadProjectionMatrix(m_ProjectionMatrix);
	shader.Unbind();
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
	// Tell opengl to test for depth
	GLCall(glEnable(GL_DEPTH_TEST));
	// Set clear color and clear the screen
	GLCall(glClearColor(1.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Render(Entity& entity, BasicShader& shader)
{
	// Get textured model and raw model
	TexturedModel texmodel = entity.GetModel();
	RawModel frame = texmodel.GetRawModel();
	// Bind the model's VAO
	GLCall(glBindVertexArray(frame.VaoID()));
	// Enable the attrib arrays / layout locations
	GLCall(glEnableVertexAttribArray(0)); // positions
	GLCall(glEnableVertexAttribArray(1)); // texture coordinates
	// Load transformation matrix for this entity into the shader
	shader.LoadTransformMatrix(Math::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	// Activate an OpenGL texture and tell it where the texture is
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, texmodel.GetTexture().ID()));
	// Draw the model
	GLCall(glDrawElements(GL_TRIANGLES, frame.VertexCount(), GL_UNSIGNED_INT, 0)); // TODO: abstract such that vertex count, type of 3rd param
	                                                                                     //       and offset are not hard coded.
	// Disable attrib arrays / layout locations
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glBindVertexArray(0));
}

