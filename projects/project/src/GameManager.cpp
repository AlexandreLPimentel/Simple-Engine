///////////////////////////////////////////////////////////////////////
//
// Drawing two instances of a triangle in Modern OpenGL.
// A "hello world" of Modern OpenGL.
//
// Assignment : Create Shader Abstraction 
//					(e.g. check compilation/linkage for errors, read from file) 
//			  : Manage Multiple Drawable Entities (using your vertex and matrix classes)
//              Draw a set of 7 TANs (i.e. TANGRAM shapes) of different colors: 
//              (1) 3 different TAN geometric shapes at the origin:
//					- right triangle
//					- square
//					- parallelogram
//              (2) 7 TANs of different colors put together to form a shape of your choice:
//					- 2 big right triangles
//					- 1 medium right triangle
//					- 2 small right triangles
//					- 1 square
//					- 1 parallelogram;
//
// (c) 2013-17 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////


#include "GameManager.h"

#define CAPTION "Hello Modern 2D World"

#define VERTICES 0
#define COLORS 1

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
	GLint result = GL_FALSE;
	int logLength;

	const GLchar* vertexShaderSrc = vertexShader.shaderProgram.c_str();
	const GLchar* fragmentShaderSrc = fragmentShader.shaderProgram.c_str();

	//VERTEX SHADER
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &vertexShaderSrc, 0);
	glCompileShader(VertexShaderId);


	glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(VertexShaderId, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(VertexShaderId, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;

	//FRAGMENT SHADER
	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &fragmentShaderSrc, 0);
	glCompileShader(FragmentShaderId);

	glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> fragmentShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(FragmentShaderId, logLength, NULL, &fragmentShaderError[0]);
	std::cout << &fragmentShaderError[0] << std::endl;

	//LINKING
	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glBindAttribLocation(ProgramId, VERTICES, "in_Position");
	glBindAttribLocation(ProgramId, COLORS, "in_Color");
	glLinkProgram(ProgramId);
	UniformId = glGetUniformLocation(ProgramId, "Matrix");

	checkOpenGLError("ERROR: Could not create shaders.");
}

void GameManager::destroyShaderProgram()
{
	glUseProgram(0);
	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);
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
		glBindVertexArray(gameObjects[i].VaoId);
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

void GameManager::idle()
{
	glutPostRedisplay();
}

void GameManager::reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
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
	gameObjects[0] = GameObject::triangle(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	gameObjects[0].translate(mat4::translationMatrix(vec3(-1.0f * SIZE_RATIO, 0.5f * SIZE_RATIO, 0.0f)));
	
	gameObjects[1] = GameObject::triangle(vec4(1.0f, 1.0f, 0.5f, 1.0f));
	gameObjects[1].translate(mat4::translationMatrix(vec3(-1.5f * SIZE_RATIO, 2.0f * SIZE_RATIO, 0.0f)));
	gameObjects[1].rotate(mat4::zRotationMatrix(90.0f));
	
	//medium triangle
	gameObjects[2] = GameObject::triangle(vec4(1.0f, 0.5f, 1.0f, 1.0f));
	gameObjects[2].translate(mat4::translationMatrix(vec3(0.5f * SIZE_RATIO, 0.5f * SIZE_RATIO, 0.0f)));
	gameObjects[2].rotate(mat4::zRotationMatrix(135.0f));
	gameObjects[2].scale(mat4::scaleMatrix(sqrt(2)));

	//big triangles
	gameObjects[3] = GameObject::triangle(vec4(0.0f, 1.0f, 1.0f, 1.0f));
	gameObjects[3].translate(mat4::translationMatrix(vec3(-0.7125f * SIZE_RATIO, -0.7125f * SIZE_RATIO, 0.0f)));
	gameObjects[3].rotate(mat4::zRotationMatrix(45.0f));
	gameObjects[3].scale(mat4::scaleMatrix(2));

	gameObjects[4] = GameObject::triangle(vec4(0.5f, 0.5f, 1.0f, 1.0f));
	gameObjects[4].translate(mat4::translationMatrix(vec3(0.6875f * SIZE_RATIO, -2.125f * SIZE_RATIO, 0.0f)));
	gameObjects[4].rotate(mat4::zRotationMatrix(-135.0f));
	gameObjects[4].scale(mat4::scaleMatrix(2));

	//square
	gameObjects[5] = GameObject::square(vec4(1.0f, 0.5f, 0.5f, 1.0f));
	gameObjects[5].translate(mat4::translationMatrix(vec3(1.0f * SIZE_RATIO, 2.0f * SIZE_RATIO, 0.0f)));

	//parallelogram
	gameObjects[6] = GameObject::parallelogram(vec4(0.5f, 1.0f, 0.5f, 1.0f));
	gameObjects[6].translate(mat4::translationMatrix(vec3(-0.50f * SIZE_RATIO, 1.5f * SIZE_RATIO, 0.0f)));
	gameObjects[6].rotate(mat4::zRotationMatrix(90.0f));


	for (int i = 0; i < 7; i++) {
		glGenVertexArrays(1, &gameObjects[i].VaoId);
		glBindVertexArray(gameObjects[i].VaoId);
		{
			glGenBuffers(2, gameObjects[i].VboId);

			glBindBuffer(GL_ARRAY_BUFFER, gameObjects[i].VboId[0]);
			glBufferData(GL_ARRAY_BUFFER, gameObjects[i].wholeVertexBufferSize(), gameObjects[i].vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(gameObjects[i].vertexBufferSize()));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gameObjects[i].VboId[1]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, gameObjects[i].indexBufferSize(), gameObjects[i].indices, GL_STATIC_DRAW);
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