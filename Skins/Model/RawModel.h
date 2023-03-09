#pragma once

#include <GL/glew.h>

class RawModel
{
public:
	RawModel(GLuint vaoID, unsigned int vertexCount) : m_VaoID(vaoID), m_VertexCount(vertexCount) {}

	inline GLuint VaoID() const { return m_VaoID; }
	inline unsigned int VertexCount() const { return m_VertexCount; }

private:
	GLuint m_VaoID;
	unsigned int m_VertexCount;
};