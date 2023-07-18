#pragma once

#include "RawModel.h"
#include "Render/Loader.h"

class Terrain
{
public:
	static const float SIZE;
	static const int VERTEX_COUNT = 128;

private:
	float m_X;
	float m_Z;

	RawModel m_RawModel;
	Texture m_Texture;

	RawModel generateTerrain(Loader* loader);

public:
	Terrain(int gridX, int gridZ, Loader* loader, const Texture& texture);
	~Terrain();

	inline float getX() const					{ return m_X; }
	inline float getZ() const					{ return m_Z; }
	inline RawModel getRawModel() const		{ return m_RawModel; }
	inline Texture getTexture() const			{ return m_Texture; }
};
