#include "Renderer.h"
#include "Log.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
	// Set clear color and clear the screen
	GLCall(glClearColor(1.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Render(const TexturedModel& texturedModel) const
{
	// Get the rawmodel from the texturedmodel
	RawModel frame = texturedModel.GetRawModel();
	// Bind the model's VAO
	GLCall(glBindVertexArray(frame.VaoID()));
	// Enable the attrib arrays / layout locations
	GLCall(glEnableVertexAttribArray(0)); // positions
	GLCall(glEnableVertexAttribArray(1)); // texture coordinates
	// Activate an OpenGL texture and tell it where the texture is
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, texturedModel.GetTexture().ID()));
	// Draw the model
	GLCall(glDrawElements(GL_TRIANGLES, frame.VertexCount(), GL_UNSIGNED_INT, 0)); // TODO: abstract such that vertex count, type of 3rd param
	                                                                                     //       and offset are not hard coded.
	// Disable attrib arrays / layout locations
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glBindVertexArray(0));
}

