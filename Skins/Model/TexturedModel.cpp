#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel& model, const Texture& texture)
	: m_RawModel(model), m_Texture(texture)
{
}

TexturedModel::~TexturedModel()
{
}

RawModel TexturedModel::GetRawModel() const
{
	return m_RawModel;
}

Texture TexturedModel::GetTexture() const
{
	return m_Texture;
}

