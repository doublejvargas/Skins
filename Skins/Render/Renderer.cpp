#include "Renderer.h"
#include "Log.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Prepare() const
{
	// Set clear color and clear the screen
	GLCall(glClearColor(1.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Render(const RawModel& model) const
{
	GLCall(glBindVertexArray(model.VaoID()));
	GLCall(glEnableVertexAttribArray(0)); // hard coded 0 because it is the only one we're using for this part -- the positions

	// Draw the model
	GLCall(glDrawArrays(GL_TRIANGLES, 0, model.VertexCount()));

	GLCall(glDisableVertexAttribArray(0));
	GLCall(glBindVertexArray(0));
}

