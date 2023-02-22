#include "Loader.h"
#include "Log.h"

Loader::Loader()
{
	m_VAOS.clear();
	m_VBOS.clear();
}

Loader::~Loader()
{
	while (m_VBOS.size() > 0)
	{
		GLCall(glDeleteBuffers(1, &m_VBOS.back()));
		GLCall(m_VBOS.pop_back());
	}

	while (m_VAOS.size() > 0)
	{
		GLCall(glDeleteBuffers(1, &m_VAOS.back()));
		m_VAOS.pop_back();
	}
}

RawModel Loader::LoadToVAO(const void* data, const unsigned int* indices, unsigned int numVertices, unsigned int numIndices)
{
	// Create a new VAO
	GLuint vaoID = CreateVAO();
	BindIndicesBuffer(indices, numIndices); // TODO: does this matter here?
	StoreDataInAttributeList(0, data, numVertices);
	UnbindVAO();
	return RawModel(vaoID, numVertices);
}

void Loader::UnbindVAO() const
{
	GLCall(glBindVertexArray(0));
}

GLuint Loader::CreateVAO()
{
	GLuint vaoID;
	// Create a new VAO
	GLCall(glGenVertexArrays(1, &vaoID));
	// Store the VAO in our local list
	m_VAOS.push_back(vaoID);
	// Bind the VAO to use it
	GLCall(glBindVertexArray(vaoID));
	
	return vaoID;
}

void Loader::StoreDataInAttributeList(GLuint layoutloc , const void* data, unsigned int count)
{
	GLuint vboID;
	// Create new buffer
	GLCall(glGenBuffers(1, &vboID));
	// Store the buffer in our local list
	m_VBOS.push_back(vboID);
	// Bind the buffer to use it
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	// Store the data in the buffer
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(data), data, GL_STATIC_DRAW)); // TODO: May need to change to dynamic draw in future.
	// Tell OpenGL how and where to store this VBO in the VAO
	GLCall(glVertexAttribPointer(layoutloc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0)); // TODO: refer to cherno's project on how to abstract this function
}

void Loader::BindIndicesBuffer(const unsigned int* indices, unsigned int count)
{
	GLuint iboID;
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GLCall(glGenBuffers(1, &iboID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW)) // TODO: may need to change to dynamic draw in future.
}

