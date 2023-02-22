#pragma once

#include "RawModel.h"
#include "Textures/Texture.h"

class TexturedModel
{
public:
	TexturedModel(const RawModel& model, const Texture& texture);
	virtual ~TexturedModel();

	RawModel GetRawModel() const;
	Texture GetTexture() const;

private:
	RawModel m_RawModel;
	Texture m_Texture;
};
