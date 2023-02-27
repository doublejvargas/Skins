#include "Loader.h"
#include "Log.h"
#include <cassert>
#include "vendor/stb_image/stb_image.h"

Loader::Loader()
{
	m_VAOS.clear();
	m_VBOS.clear();
	m_IBOS.clear();
	m_Textures.clear();
}

Loader::~Loader()
{
	// Loop through all the storage arrays and delete OpenGL variables
	while (m_VAOS.size() > 0)
	{
		GLCall(glDeleteVertexArrays(1, &m_VAOS.back()));
		m_VAOS.pop_back();
	}
	while (m_VBOS.size() > 0)
	{
		GLCall(glDeleteBuffers(1, &m_VBOS.back()));
		m_VBOS.pop_back();
	}
	while (m_IBOS.size() > 0)
	{
		GLCall(glDeleteBuffers(1, &m_IBOS.back()));
		m_IBOS.pop_back();
	}
	while (m_Textures.size() > 0)
	{
		GLCall(glDeleteTextures(1, &m_Textures.back()));
		m_Textures.pop_back();
	}
}

RawModel Loader::LoadToVAO(const void* positions, const int* indices, const void* texCoords,
			unsigned int numVertices, unsigned int numIndices, unsigned int numTexCoords)
{
	// Create a new VAO
	GLuint vaoID = CreateVAO();
	BindIndicesBuffer(indices, numIndices);
	// positions in layout location/attrib location 0
	StoreDataInAttributeList(0, 3, numVertices, GL_FLOAT, positions);
	// texture coordinates in layout location/attrib location 1
	StoreDataInAttributeList(1, 2, numTexCoords, GL_FLOAT, texCoords);
	UnbindVAO();
	
	return RawModel(vaoID, numIndices);
}

GLuint Loader::LoadTexture(const std::string& path)
{
	GLuint id;
	int width, height, bpp;
	// Load image data
	unsigned char* databuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
	if (!databuffer)
	{
		std::cerr << "ERROR: texture loading failed for: " << path << std::endl;
		return -1;
	}
	// Generate and bind a OpenGL texture
	GLCall(glGenTextures(1, &id));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));
	// Tell OpenGL how to fill an area that's too big or too small
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// Tell OpenGL to clamp textures to edge (so you don't get transparent gaps)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	// Store the OpenGL texture data
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, databuffer));
	// Unbind texture
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	// Store the buffer in the list
	m_Textures.push_back(id);
	// Unload image data
	stbi_image_free(databuffer);

	return id;
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

void Loader::StoreDataInAttributeList(GLuint layoutloc, unsigned int dimension, unsigned int count, GLenum type, const void* data)
{
	// helps determine the size of buffer to be allocated by gpu in glBufferData
	unsigned int size = sizeof(float);
	switch (type)
	{
	case GL_UNSIGNED_INT:		size = sizeof(unsigned int);
	case GL_INT:				size = sizeof(int);
	case GL_UNSIGNED_BYTE:		size = sizeof(char);
	case GL_BYTE:				size = sizeof(signed char);
	case GL_SHORT:				size = sizeof(short);
	case GL_DOUBLE:				size = sizeof(double);
	default:					size = sizeof(float);
	}
	GLbyte; GLchar;

	GLuint vboID;
	// Create new buffer
	GLCall(glGenBuffers(1, &vboID));
	// Store the buffer in our local list
	m_VBOS.push_back(vboID);
	// Bind the buffer to use it
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	// Store the data in the buffer
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * size, data, GL_STATIC_DRAW)); // TODO: May need to change to dynamic draw in future.
	// Tell OpenGL how and where to store this VBO in the VAO
	GLCall(glVertexAttribPointer(layoutloc, dimension, type, GL_FALSE, 0, nullptr)); // TODO: refer to cherno's project on how to abstract this function
}

void Loader::BindIndicesBuffer(const int* indices, unsigned int count)
{
	GLuint iboID;
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	// Generate buffer and bind for use
	GLCall(glGenBuffers(1, &iboID));
	// Store in our local list
	m_IBOS.push_back(iboID);
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID));
	// Store the data in the buffer in opengl/ gpu
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(int), indices, GL_STATIC_DRAW)) // TODO: may need to change to dynamic draw in future.
}

