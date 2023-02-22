#pragma once

#include <GL/glew.h>

class RawModel
{
public:
	RawModel(GLuint vaoID, unsigned int vertexCount);
	virtual ~RawModel();

	GLuint VaoID() const;
	unsigned int VertexCount() const;

private:
	GLuint m_VaoID;
	unsigned int m_VertexCount;
};