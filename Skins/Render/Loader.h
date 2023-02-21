#pragma once

#include "RawModel.h"
#include <GL/glew.h>
#include <vector>


class Loader
{
public:
	Loader();
	virtual ~Loader();

	RawModel LoadToVAO(const void* data, unsigned int count);
	void UnbindVAO() const;

private:
	std::vector<GLuint> m_VAOS;
	std::vector<GLuint> m_VBOS;
	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint attribNumber, const void* data, unsigned int count);
};