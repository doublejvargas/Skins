#include "RawModel.h"


RawModel::RawModel(GLuint vaoID, unsigned int vertexCount)
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

unsigned int RawModel::VertexCount() const
{
	return m_VertexCount;
}

