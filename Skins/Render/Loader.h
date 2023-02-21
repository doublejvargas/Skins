#pragma once

#include "RawModel.h"
#include <GL/glew.h>
#include <vector>


class Loader
{
public:
	Loader();
	virtual ~Loader();

	RawModel LoadToVAO(const void* data, const unsigned int* indices, unsigned int numVertices, unsigned int numIndices);
	void UnbindVAO() const;

private:
	std::vector<GLuint> m_VAOS;
	std::vector<GLuint> m_VBOS;
	
	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint attribNumber, const void* data, unsigned int count);
	void BindIndicesBuffer(const unsigned int* indices, unsigned int count);
};