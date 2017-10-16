#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class shader
{
public:
	std::string shaderProgram;
	shader(char* filename);
	~shader();
	//void load(char* filename);
};

