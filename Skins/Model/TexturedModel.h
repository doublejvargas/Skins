#pragma once

#include "RawModel.h"
#include "Textures/Texture.h"

class TexturedModel
{
public:
	TexturedModel(const RawModel& model, const Texture& texture) : m_RawModel(model), m_Texture(texture) {}

	inline RawModel GetRawModel() const { return m_RawModel; }
	inline Texture GetTexture() const { return m_Texture; }

private:
	RawModel m_RawModel;
	Texture m_Texture;
};
