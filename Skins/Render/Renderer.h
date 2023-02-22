#pragma once

//#include "Model/RawModel.h" //includes GL/glew.h
#include "Model/TexturedModel.h" // includes rawmodel which also includes GL/glew

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void Clear() const;
	void Render(const TexturedModel& texturedModel) const;
};