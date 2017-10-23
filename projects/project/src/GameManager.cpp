///////////////////////////////////////////////////////////////////////
//
// Assignment consists in the following:
//
// - Create the following changes to your scene, making it fully 3D:
//   - Extrude your TANs into the 3rd dimension. The TANs should have
//     slightly different "heights".
//   - The new faces of each TAN should share the same hue as the 
//     original top face color but have different levels of saturation 
//     and brightness.
//
// - Add the following functionality:
//   - Create a View Matrix from (eye, center, up) parameters.
//   - Create an Orthographic Projection Matrix from (left-right, 
//     bottom-top, near-far) parameters.
//   - Create a Perspective Projection Matrix from (fovy, aspect,
//     nearZ, farZ) parameters.
//
// - Add the following dynamics to the application:
//   - Create a free 3D camera controlled by the mouse allowing to 
//     visualize the scene through all its angles.
//   - Change perspective from orthographic to perspective and back as
//     a response to pressing the key 'p'.
//
// (c) 2013-17 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////


#include "GameManager.h"

#define CAPTION "Hello Modern 2D World"

#define VERTICES 0
#define COLORS 1
#define OFFSET 0.01f

/////////////////////////////////////////////////////////////////////// ERRORS

bool GameManager::isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void GameManager::checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}


/////SHADERS


void GameManager::createShaderProgram()
{
	vertexShader.setup(GL_VERTEX_SHADER);
	fragmentShader.setup(GL_FRAGMENT_SHADER);

	ProgramId = glCreateProgram();
	vertexShader.attach(ProgramId);
	fragmentShader.attach(ProgramId);

	vertexShader.bind(VERTICES, "in_Position");
	fragmentShader.bind(COLORS, "in_Color");

	glLinkProgram(ProgramId);
	UniformId = glGetUniformLocation(ProgramId, "ModelMatrix");
	UboId = glGetUniformBlockIndex(ProgramId, "SharedMatrices");
	glUniformBlockBinding(ProgramId, UboId, UBO_BP);

	checkOpenGLError("ERROR: Could not create shaders.");
}

void GameManager::destroyShaderProgram()
{
	glUseProgram(0);
	vertexShader.destroy();
	fragmentShader.destroy();
	glDeleteProgram(ProgramId);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}




/////DRAW CYCLE


GameManager::GameManager()
{
}

void GameManager::timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
	FrameCount = 0;
}

void GameManager::keyTimer(int value) {
	ViewMatrix *= mat4::translationMatrix(vec3(d * OFFSET - a * OFFSET, w * OFFSET - s * OFFSET, r * OFFSET - l * OFFSET));
}

void GameManager::cleanup()
{
	destroyShaderProgram();
	destroyBufferObjects();
}

void GameManager::draw()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawScene();
	glutSwapBuffers();
}

void GameManager::drawScene()
{

	glUseProgram(ProgramId);

	for (int i = 0; i < 7; i++) {
		gameObjects[i].draw(UniformId);
	}

	glUseProgram(0);
	glBindVertexArray(0);

	checkOpenGLError("ERROR: Could not draw scene.");
}

void GameManager::display()
{
	timeNow = glutGet(GLUT_ELAPSED_TIME);
	if (timeLast + delta <= timeNow) {
		timeLast = timeNow;
		draw();
	}
}

void GameManager::keyboard(unsigned char key, int x, int y, bool up)
{
	bool pressed = !up;
	switch (key) {
	case 'p':
		if (!up) {
			if (currentProjection == 0) {
				currentProjection = 1;
				ProjectionMatrix = &ProjectionMatrixPerspective;
			}
			else {
				currentProjection = 0;
				ProjectionMatrix = &ProjectionMatrixOrtho;
			}
		}
		break;
	case 'w':
		w = pressed;
		break;
	case 's':
		s = pressed;
		break;
	case 'a':
		a = pressed;
		break;
	case 'd':
		d = pressed;
		break;
	}
}

void GameManager::mouse(int button, int state, int x, int y)
{
	bool pressed = (state == GLUT_DOWN);
	switch (button) {
	case GLUT_LEFT_BUTTON:
		l = pressed;
		break;
	case GLUT_RIGHT_BUTTON:
		r = pressed;
		break;
	}
}

void GameManager::mouseMovement(float x, float y)
{
	ViewMatrix *= mat4::xRotationMatrix((mouseY - y));
	ViewMatrix *= mat4::yRotationMatrix((mouseX - x));
	mouseX = x;
	mouseY = y;
}

void GameManager::idle()
{
	glutPostRedisplay();
}

void GameManager::reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
	ProjectionMatrixOrtho = mat4::ortho(-w/100, w/100, -h/100, h/100, 1, 10);
	ProjectionMatrixPerspective = mat4::perspective(30, -w/h, 1, 10);
}

void GameManager::init(int argc, char* argv[]) {
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	createShaderProgram();
	createBufferObjects();
}

/////OBJECTS


void GameManager::createBufferObjects()
{
	//t*r*s

	//small triangles
	gameObjects[0] = GameObject::triangle(vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.05f);
	gameObjects[0].translate(mat4::translationMatrix(vec3(-1.0f, 0.5f, 0.0f)));

	gameObjects[1] = GameObject::triangle(vec4(1.0f, 1.0f, 0.5f, 1.0f), 0.1f);
	gameObjects[1].translate(mat4::translationMatrix(vec3(-1.5f, 2.0f, 0.0f)));
	gameObjects[1].rotate(mat4::zRotationMatrix(90.0f));

	//medium triangle
	gameObjects[2] = GameObject::triangle(vec4(1.0f, 0.5f, 1.0f, 1.0f), 0.15f);
	gameObjects[2].translate(mat4::translationMatrix(vec3(0.5f, 0.5f, 0.0f)));
	gameObjects[2].rotate(mat4::zRotationMatrix(135.0f));
	gameObjects[2].scale(mat4::scaleMatrix((float)sqrt(2)));

	//big triangles
	gameObjects[3] = GameObject::triangle(vec4(0.0f, 1.0f, 1.0f, 1.0f), 0.2f);
	gameObjects[3].translate(mat4::translationMatrix(vec3(-0.7125f, -0.7125f, 0.0f)));
	gameObjects[3].rotate(mat4::zRotationMatrix(45.0f));
	gameObjects[3].scale(mat4::scaleMatrix(2));

	gameObjects[4] = GameObject::triangle(vec4(0.5f, 0.5f, 1.0f, 1.0f), 0.25f);
	gameObjects[4].translate(mat4::translationMatrix(vec3(0.70f, -2.125f, 0.0f)));
	gameObjects[4].rotate(mat4::zRotationMatrix(-135.0f));
	gameObjects[4].scale(mat4::scaleMatrix(2));

	//square
	gameObjects[5] = GameObject::square(vec4(1.0f, 0.5f, 0.5f, 1.0f), 0.3f);
	gameObjects[5].translate(mat4::translationMatrix(vec3(1.0f, 2.0f, 0.0f)));

	//parallelogram
	gameObjects[6] = GameObject::parallelogram(vec4(0.5f, 1.0f, 0.5f, 1.0f), 0.35f);
	gameObjects[6].translate(mat4::translationMatrix(vec3(-0.50f, 1.5f, 0.0f)));
	gameObjects[6].rotate(mat4::zRotationMatrix(90.0f));


	for (int i = 0; i < 7; i++) {
		gameObjects[i].ProjectionMatrix = &ProjectionMatrix;
		gameObjects[i].ViewMatrix = &ViewMatrix;
		glGenVertexArrays(1, &gameObjects[i].VaoId);
		glBindVertexArray(gameObjects[i].VaoId);
		{
			glGenBuffers(3, gameObjects[i].VboId);

			glBindBuffer(GL_ARRAY_BUFFER, gameObjects[i].VboId[0]);
			glBufferData(GL_ARRAY_BUFFER, gameObjects[i].wholeVertexBufferSize(), gameObjects[i].vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(gameObjects[i].vertexBufferSize()));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gameObjects[i].VboId[1]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, gameObjects[i].indexBufferSize(), gameObjects[i].indices, GL_STATIC_DRAW);

			glBindBuffer(GL_UNIFORM_BUFFER, gameObjects[i].VboId[2]);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) * 2, 0, GL_STREAM_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, gameObjects[i].VboId[2]);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void GameManager::destroyBufferObjects()
{

	for (int i = 0; i < 7; i++) {
		glBindVertexArray(gameObjects[i].VaoId);
		glDisableVertexAttribArray(VERTICES);
		glDisableVertexAttribArray(COLORS);
		glDeleteBuffers(2, gameObjects[i].VboId);
		glDeleteVertexArrays(1, &gameObjects[i].VaoId);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}


/////////////////////////////////////////////////////////////////////// SETUP


void GameManager::checkOpenGLInfo()
{
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void GameManager::setupOpenGL()
{
	checkOpenGLInfo();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void GameManager::setupGLEW()
{
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
}

void GameManager::setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if (WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}