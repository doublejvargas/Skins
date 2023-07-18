#include "Terrain.h"
#include "glm/glm.hpp"
#include <vector>

const float Terrain::SIZE = 800.0f;

Terrain::Terrain(int gridX, int gridZ, Loader* loader, const Texture& texture)
{
	m_X = gridX * SIZE;
	m_Z = gridZ * SIZE;
	m_Texture = texture;
	m_RawModel = generateTerrain(loader);
}

Terrain::~Terrain()
{
}

RawModel Terrain::generateTerrain(Loader* loader)
{
	int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices(6*(VERTEX_COUNT - 1)*(VERTEX_COUNT - 1), 0);

	for (int z = 0; z < VERTEX_COUNT; z++ )
	{
		for (int x = 0; x < VERTEX_COUNT; x++)
		{
			float posX, posZ, texX, texZ;
			posX = (float)x / ((float)VERTEX_COUNT - 1) * SIZE;
			posZ = (float)z / ((float)VERTEX_COUNT - 1) * SIZE;
			positions.push_back(glm::vec3(posX, 0, posZ));

			normals.push_back(glm::vec3(0, 1, 0));

			texX = (float)x / ((float)VERTEX_COUNT - 1);
			texZ = (float)z / ((float)VERTEX_COUNT - 1);

			textureCoords.push_back(glm::vec2(texX, texZ));
		}
	}

	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
	{
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
		{
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices.at(pointer++) = topLeft;
			indices.at(pointer++) = bottomLeft;
			indices.at(pointer++) = topRight;
			indices.at(pointer++) = topRight;
			indices.at(pointer++) = bottomLeft;
			indices.at(pointer++) = bottomRight;
		}
	}

	return loader->LoadToVAO(positions, textureCoords, normals, indices);
}

