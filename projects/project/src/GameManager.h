#pragma once
#include "AbstractGameManager.h"
#include "vector.h"
#include "matrix.h"
#include "shader.h"
#include "GameObject.h"

class GameManager : public AbstractGameManager {
private:
	int WinX = 600, WinY = 600;
	float mouseX, mouseY;
	bool w, a, s, d, l, r;
	int WindowHandle = 0;
	unsigned int FrameCount = 0;
	unsigned const FPSLimit = 60;
	long timeLast = 0;
	long timeNow = 0;
	double const delta = 1.0 / FPSLimit * 1000;
	shader vertexShader = shader("./src/glsl/basic.vert");
	shader fragmentShader = shader("./src/glsl/basic.frag");
	GameObject gameObjects[7];
	GLuint ProgramId;
	GLint UboId, UniformId;
	const GLuint UBO_BP = 0;
	int currentProjection = 0;
	mat4 *ProjectionMatrix = &ProjectionMatrixOrtho;
	mat4 ProjectionMatrixOrtho = mat4::ortho(-5, 5, -5, 5, 1, 10);
	mat4 ProjectionMatrixPerspective = mat4::perspective(30, -1, 1, 10);
	mat4 ViewMatrix = mat4::lookAt(vec3(0, 0, -5), vec3(0, 0, 0), vec3(0, -1, 0));
public:
	GameManager();
	void timer(int value);
	void keyTimer(int value);
	void cleanup();
	void draw();
	void drawScene();
	void display();
	void keyboard(unsigned char key, int x, int y, bool up);
	void mouse(int button, int state, int x, int y);
	void mouseMovement(float x, float y);
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