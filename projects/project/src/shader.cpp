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

