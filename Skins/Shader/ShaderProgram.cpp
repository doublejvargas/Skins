#include <iostream>
#include <fstream>
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
		std::cerr << "ERROR: could not validate program \n" << infoLog << std::endl;
		// Delete the array
		delete infoLog;
	}
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

void ShaderProgram::Bind()
{
	GLCall(glUseProgram(m_ProgramID));
}

void ShaderProgram::Unbind()
{
	GLCall(glUseProgram(0));
}

GLuint ShaderProgram::LoadShader(const std::string& filename, GLenum type)
{
	// Open the file
	std::ifstream file;
	file.open(filename.c_str());

	// temp variables
	std::string source, line;

	if (file.is_open())
	{
		// Load file to string
		while (file.good())
		{
			getline(file, line);
			source.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}
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
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		GLCall(glDeleteShader(0));
		return 0;
	}

	return id;
}

void ShaderProgram::BindAttribute(unsigned int layout_location, const std::string& name)
{
	GLCall(glBindAttribLocation(m_ProgramID, layout_location, name.c_str()));
}

