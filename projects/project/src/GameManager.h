#pragma once
#include "AbstractGameManager.h"
#include "vector.h"
#include "matrix.h"
#include "shader.h"
#include "GameObject.h"

class GameManager : public AbstractGameManager {
private:
	int WinX = 600, WinY = 600;
	int WindowHandle = 0;
	unsigned int FrameCount = 0;
	unsigned const FPSLimit = 60;
	long timeLast = 0;
	long timeNow = 0;
	double const delta = 1.0 / FPSLimit * 1000;
	shader vertexShader = shader("./src/glsl/basic.vert");
	shader fragmentShader = shader("./src/glsl/basic.frag");
	GameObject gameObjects[7];
	GLuint VertexShaderId, FragmentShaderId, ProgramId;
	GLint UniformId;
public:
	GameManager();
	void timer(int value);
	void cleanup();
	void draw();
	void drawScene();
	void display();
	void idle();
	void reshape(int w, int h);
	void init(int argc, char* argv[]);
	void checkOpenGLInfo();
	void setupOpenGL();
	void setupGLEW();
	void setupGLUT(int argc, char* argv[]);
	bool isOpenGLError();
	void checkOpenGLError(std::string error);
	void createShaderProgram();
	void destroyShaderProgram();
	void createBufferObjects();
	void destroyBufferObjects();
};