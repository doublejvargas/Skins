#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include "Model/TexturedModel.h"


class Loader
{
public:
	Loader();
	virtual ~Loader();

	/* NOTE: we need to pass the "num" parameters to keep track of the sizes of arrays.. sizeof(positions) will return the size of first
	*  element, which will then cause problems in StoreDataInAttributeList and BindIndicesBuffer --
	*  more specifically the call to "glBufferData" will cause for a buffer of inappropriate size to be allocated, the data won't be
	*  stored in the gpu, and then no image "mysteriously" displayed. Pain in the butt figuring this one out. */ 
	RawModel LoadToVAO(const void* positions, const int* indices, const void* texCoords, 
		unsigned int numVertices, unsigned int numIndices, unsigned int numTexCoords);
	GLuint LoadTexture(const std::string& filename);
	void UnbindVAO() const;

private:
	std::vector<GLuint> m_VAOS;
	std::vector<GLuint> m_VBOS;
	std::vector<GLuint> m_IBOS;
	std::vector<GLuint> m_Textures;

	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint layoutloc, unsigned int dimension, unsigned int count, GLenum type, const void* data);
	void BindIndicesBuffer(const int* indices, unsigned int count);
};