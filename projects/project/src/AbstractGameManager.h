#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"

class AbstractGameManager
{
public:
	virtual void timer(int value) = 0;
	virtual void keyTimer(int value) = 0;
	virtual void cleanup() = 0;
	virtual void display() = 0;
	virtual void idle() = 0;
	virtual void reshape(int w, int h) = 0;
	virtual void keyboard(unsigned char key, int x, int y, bool up) = 0;
	virtual void mouse(int button, int state, int x, int y) = 0;
	virtual void mouseMovement(float x, float y) = 0;
	virtual void checkOpenGLInfo() = 0;
	virtual void setupOpenGL() = 0;
	virtual void setupGLEW() = 0;
	virtual void setupGLUT(int argc, char* argv[]) = 0;
	virtual void init(int argc, char* arv[]) = 0;
};

