#pragma once

#include "Model/TexturedModel.h"
#include <GL/glew.h>
#include <vector>
#include <string>


class Loader
{
public:
	Loader();
	virtual ~Loader();

	RawModel LoadToVAO(const void* positions, const unsigned int* indices, const void* texCoords, 
		unsigned int numVertices, unsigned int numIndices, unsigned int numTexCoords);
	GLuint LoadTexture(const std::string& filename);
	void UnbindVAO() const;

private:
	std::vector<GLuint> m_VAOS;
	std::vector<GLuint> m_VBOS;
	std::vector<GLuint> m_IBOS;
	std::vector<GLuint> m_Textures; // Texture cache

	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint layoutloc, unsigned int dimension, unsigned int count, GLenum type, const void* data);
	void BindIndicesBuffer(const unsigned int* indices, unsigned int count);
};