#include "shader.h"



shader::shader(char* filename)
{

	std::ifstream fileStream(filename, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		shaderProgram = shaderProgram + line + "\n";
	}

	fileStream.close();
}


shader::~shader()
{
}

void shader::setup(GLenum type)
{
	GLint result = GL_FALSE;
	int logLength;

	const GLchar* shaderSrc = shaderProgram.c_str();

	shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &shaderSrc, 0);
	glCompileShader(shaderId);

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> shaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shaderId, logLength, NULL, &shaderError[0]);
	std::cout << &shaderError[0] << std::endl;

}

void shader::attach(GLuint programId)
{
	this->programId = programId;
	glAttachShader(programId, shaderId);
}

void shader::bind(GLuint index, const char * name)
{
	glBindAttribLocation(programId, index, name);
}

void shader::destroy()
{
	glDetachShader(programId, shaderId);
	glDeleteShader(shaderId);
}

