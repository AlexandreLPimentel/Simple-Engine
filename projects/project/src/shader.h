#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class shader
{
private:
	GLuint shaderId;
	GLuint programId;
	std::string shaderProgram;
public:
	shader(char* filename);
	~shader();
	void setup(GLenum type);
	void attach(GLuint programId);
	void bind(GLuint index, const char* name);
	void destroy();
};

