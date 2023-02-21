#pragma once

#include "RawModel.h" //includes GL/glew.h

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void Prepare() const;
	void Render(const RawModel& model) const;
};