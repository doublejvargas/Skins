#include "TerrainRenderer.h"
#include "Renderer.h"
#include "Log.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Toolbox/Math.h"
#include "Model/TexturedModel.h"

TerrainRenderer::TerrainRenderer(BasicShader& shader, const float& aspect)
{
	// Don't draw faces we can't see. Improves performance
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));
	// Tell OpenGL to test for depth
	GLCall(glEnable(GL_DEPTH_TEST));
	// Set clear color
	GLCall(glClearColor(0.1f, 0.4f, 0.1f, 1.0f));

	m_ProjectionMatrix = glm::perspective(FOV, aspect, NEAR_PLANE, FAR_PLANE);

	shader.Bind();
	shader.LoadProjectionMatrix(m_ProjectionMatrix);
	shader.Unbind();
}

TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void TerrainRenderer::Render(Entity& entity, BasicShader& shader)
{
	// Get textured model and raw model
	TexturedModel texmodel = entity.GetModel();
	RawModel frame = texmodel.GetRawModel();
	// Bind the model's VAO
	GLCall(glBindVertexArray(frame.VaoID()));
	// Enable the attrib arrays / layout locations
	GLCall(glEnableVertexAttribArray(0)); // positions
	GLCall(glEnableVertexAttribArray(1)); // texture coordinates
	GLCall(glEnableVertexAttribArray(2)); // normal vectors
	// Load transformation matrix for this entity into the shader
	shader.LoadTransformMatrix(Math::CreateTransformationMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale()));
	// Load shine variables from texture
	Texture texture = texmodel.GetTexture();
	shader.LoadShineVariables(texture.GetShineDamper(), texture.GetReflectivity());
	// Activate an OpenGL texture and tell it where the texture is
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, texmodel.GetTexture().ID()));
	// Draw the model
	GLCall(glDrawElements(GL_TRIANGLES, frame.VertexCount(), GL_UNSIGNED_INT, 0));

	// Disable attrib arrays / layout locations
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glDisableVertexAttribArray(2));
	// Unbind VAO
	GLCall(glBindVertexArray(0));
}

