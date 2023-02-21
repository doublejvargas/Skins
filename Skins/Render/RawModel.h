#pragma once

#include <GL/glew.h>

class RawModel
{
public:
	RawModel(GLuint vaoID, int vertexCount);
	virtual ~RawModel();

	GLuint VaoID() const;
	int VertexCount() const;

private:
	GLuint m_VaoID;
	int m_VertexCount;
};