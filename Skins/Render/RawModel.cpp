#include "RawModel.h"


RawModel::RawModel(GLuint vaoID, int vertexCount)
	: m_VaoID(vaoID), m_VertexCount(vertexCount)
{
}

RawModel::~RawModel()
{
}

GLuint RawModel::VaoID() const
{
	return m_VaoID;
}

int RawModel::VertexCount() const
{
	return m_VertexCount;
}

