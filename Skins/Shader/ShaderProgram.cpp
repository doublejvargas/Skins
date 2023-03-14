#include <stdio.h>
#include "ShaderProgram.h"
#include "Log.h"

ShaderProgram::ShaderProgram(const std::string& filename)
{
	// Load shaders from file
	m_VertexShaderID = LoadShader(filename + ".vert", GL_VERTEX_SHADER);
	m_FragmentShaderID = LoadShader(filename + ".frag", GL_FRAGMENT_SHADER);

	// Create shader program
	GLCall(m_ProgramID = glCreateProgram());
	// Attach the shaders to the program
	GLCall(glAttachShader(m_ProgramID, m_VertexShaderID));
	GLCall(glAttachShader(m_ProgramID, m_FragmentShaderID));
	//BindAttributes();
	// Link the program
	GLCall(glLinkProgram(m_ProgramID));
	GLCall(glValidateProgram(m_ProgramID));

	// Check validation status
	GLint status;
	GLCall(glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &status));
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		GLCall(glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength));
		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		GLCall(glGetProgramInfoLog(m_ProgramID, infoLogLength, NULL, infoLog));
		printf("ERROR: could not validate program \n%s\n", infoLog);
		// Delete the array
		delete[] infoLog;
	}

	//GetAllUniformLocations();
}

ShaderProgram::~ShaderProgram()
{
	Unbind();
	GLCall(glDetachShader(m_ProgramID, m_VertexShaderID));
	GLCall(glDetachShader(m_ProgramID, m_FragmentShaderID));
	GLCall(glDeleteShader(m_VertexShaderID));
	GLCall(glDeleteShader(m_FragmentShaderID));
	GLCall(glDeleteProgram(m_ProgramID));
}

void ShaderProgram::Bind() const
{
	GLCall(glUseProgram(m_ProgramID));
}

void ShaderProgram::Unbind() const
{
	GLCall(glUseProgram(0));
}

GLuint ShaderProgram::LoadShader(const std::string& filename, GLenum type)
{
	FILE* file;
	if (fopen_s(&file, filename.c_str(), "r") != 0)
	{
		printf("Failed to open: %s\n", filename.c_str());
		return -1;
	}

	std::string source;
	char buffer[1024], * token;
	while (fgets(buffer, 1024, file) != NULL)
	{
		source.append(buffer);
	}
	fclose(file);

	// Create shader id
	GLCall(GLuint id = glCreateShader(type));
	// Preparing source to load to OpenGL
	const GLchar* src = source.c_str();

	// Load source to OpenGL and compile
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));
	// Check compilation status
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		printf("Failed to compile %s\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
		GLCall(glDeleteShader(0));
		return 0;
	}

	return id;
}

void ShaderProgram::BindAttributes()
{
}

void ShaderProgram::BindAttribute(unsigned int layout_location, const std::string& name)
{
	GLCall(glBindAttribLocation(m_ProgramID, layout_location, name.c_str()));
}

void ShaderProgram::GetAllUniformLocations()
{
}

GLuint ShaderProgram::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_ProgramID, name.c_str()));
	if (location == -1)
		printf("Warning: uniform %s doesn't exist!\n", name.c_str());

	m_UniformLocationCache[name] = location;
	return location;
}

void ShaderProgram::SetUniform1f(GLuint location, float value)
{
	GLCall(glUniform1f(location, value));
}

void ShaderProgram::SetUniformVec3f(GLuint location, const glm::vec3& value)
{
	GLCall(glUniform3f(location, value.x, value.y, value.z));
}

void ShaderProgram::SetUniformBool(GLuint location, bool value)
{
	// if value == true, 1 else 0
	GLCall(glUniform1f(location, value ? 1.0f : 0.0f));
}

void ShaderProgram::SetUniformMat4f(GLuint location, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}

