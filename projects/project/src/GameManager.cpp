///////////////////////////////////////////////////////////////////////
//
//  Loading OBJ mesh from external file
//
//	Final individual assignment:
//	1.	Create classes: Scene, Camera and Mesh (that loads a
//		mesh from a Wavefront OBJ file) and build a small
//		scenegraph of your tangram scene (you may create more 
//		classes if needed).
//	2.	Create a ground object and couple the tangram figure
//		to the ground. Press keys to move the ground about: 
//		the tangram figure must follow the ground.
//	3.	Animate between closed puzzle (initial square) and 
//		tangram figure by pressing a key.
//	4.	Spherical camera interaction through mouse. It should
//		be possible to interact while animation is playing.
//
//	Team assignment:
//	Pick your team (3 elements from one same lab) for the team
//	assignment you will be working until the end of the semester,
//	and register it online.
//
// (c) 2013-17 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////


#include "GameManager.h"

#define CAPTION "Hello Modern 3D World"

#define VERTICES 0
#define COLORS 1
#define TEXCOORDS 2
#define NORMALS 3
#define OFFSET 0.2f

/////////////////////////////////////////////////////////////////////// ERRORS

Scene* GameManager::scene = new Scene();

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

	glBindAttribLocation(ProgramId, VERTICES, "inPosition");
	if (false)
		glBindAttribLocation(ProgramId, TEXCOORDS, "inTexcoord");
	if (true)
		glBindAttribLocation(ProgramId, NORMALS, "inNormal");

	glLinkProgram(ProgramId);
	ModelMatrix_UId = glGetUniformLocation(ProgramId, "ModelMatrix");
	ViewMatrix_UId = glGetUniformLocation(ProgramId, "ViewMatrix");
	ProjectionMatrix_UId = glGetUniformLocation(ProgramId, "ProjectionMatrix");

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
	if (!(d || a || w || s || r || l)) {
		return;
	}
	gameObjects[7].translateAll(mat4::translationMatrix(vec3(d * OFFSET - a * OFFSET, w * OFFSET - s * OFFSET, 0)), 0);
	camera.move(0, 0, l * OFFSET * 20 - r * OFFSET * 20);

	//old
	//camera.move(d * OFFSET - a * OFFSET, r * OFFSET - l * OFFSET, w * OFFSET - s * OFFSET, 0, 0);
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

	GameManager::scene->draw(ModelMatrix_UId, ViewMatrix_UId, ProjectionMatrix_UId);


	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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
		/*
		if (w != pressed) {
			cout << "w is " << (pressed ? "now pressed" : "no longer pressed") << endl;
		}
		*/
		w = pressed;
		break;
	case 's':
		/*
		if (s != pressed) {
			cout << "s is " << (pressed ? "now pressed" : "no longer pressed") << endl;
		}
		*/
		s = pressed;
		break;
	case 'a':
		/*
		if (a != pressed) {
			cout << "a is " << (pressed ? "now pressed" : "no longer pressed") << endl;
		}
		*/
		a = pressed;
		break;
	case 'd':
		/*
		if (d != pressed) {
			cout << "d is " << (pressed ? "now pressed" : "no longer pressed") << endl;
		}
		*/
		d = pressed;
		break;
	case 'q':
		exit(0);
		break;
	case 'm':
		if(pressed)
			GameManager::scene->animate();
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
	if (ignoreMouse) {
		ignoreMouse = false;
	}
	else {
		camera.move((mouseX - x)*OFFSET, (mouseY - y)*OFFSET, 0);
	}
	if (x > 3 * WinX / 4 || x < WinX / 4) {
		ignoreMouse = true;
		glutWarpPointer(WinX / 2, y);
	}
	if (y > 3 * WinY / 4 || y < WinY / 4) {
		ignoreMouse = true;
		glutWarpPointer(x, WinY / 2);
	}
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
	ProjectionMatrixOrtho = mat4::ortho((float)-w / 100, (float)w / 100, (float)h / 100, (float)-h / 100, 5, 150);
	ProjectionMatrixPerspective = mat4::perspective(25, (float)w / h, 5, 150);
}

void GameManager::init(int argc, char* argv[]) {
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	createShaderProgram();
	createBufferObjects();
	camera = Camera(vec3(0, 0, 50), vec3(0, 0, 0), vec3(0, 1, 0));
	ViewMatrix = &(camera.ViewMatrix);
}

/////OBJECTS


void GameManager::createBufferObjects()
{
	//t*r*s

	//small triangles
	gameObjects[0] = GameObject::loadMesh("./src/meshes/triangle.obj");
	//initial state
	gameObjects[0].translateAll(mat4::translationMatrix(vec3(-1.0f, 0.5f, 0.1f)), 0);
	gameObjects[0].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.1f)), 0);
	//above state
	gameObjects[0].translateAll(mat4::translationMatrix(vec3(-1.0f, 0.5f, 2.1f)), 1);
	gameObjects[0].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.1f)), 1);
	//above end state
	gameObjects[0].translateAll(mat4::translationMatrix(vec3(1.5f, 1.0f, 2.1f)), 2);
	gameObjects[0].rotateAll(qtrn::qFromAngleAxis(90, vec3(0, 0, 1)), 2);
	gameObjects[0].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.1f)), 2);
	//end state
	gameObjects[0].translateAll(mat4::translationMatrix(vec3(1.5f, 1.0f, 0.1f)), 3);
	gameObjects[0].rotateAll(qtrn::qFromAngleAxis(90, vec3(0, 0, 1)), 3);
	gameObjects[0].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.1f)), 3);
	
	gameObjects[0].canAnimate = true;

	//initial state
	gameObjects[1] = GameObject::loadMesh("./src/meshes/triangle.obj");
	gameObjects[1].translateAll(mat4::translationMatrix(vec3(-1.5f, 2.0f, 0.25f)), 0);
	gameObjects[1].rotateAll(qtrn::qFromAngleAxis(90, vec3(0, 0, 1)), 0);
	gameObjects[1].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.25f)), 0);
	//above state
	gameObjects[1].translateAll(mat4::translationMatrix(vec3(-1.5f, 2.0f, 4.25f)), 1);
	gameObjects[1].rotateAll(qtrn::qFromAngleAxis(90, vec3(0, 0, 1)), 1);
	gameObjects[1].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.25f)), 1);
	//above end state
	gameObjects[1].translateAll(mat4::translationMatrix(vec3(0.0f, -0.5f, 4.25f)), 2);
	gameObjects[1].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.25f)), 2);
	//end state
	gameObjects[1].translateAll(mat4::translationMatrix(vec3(0.0f, -0.5f, 0.25f)), 3);
	gameObjects[1].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.25f)), 3);

	gameObjects[1].canAnimate = true;

	//medium triangle
	//initial state
	gameObjects[2] = GameObject::loadMesh("./src/meshes/triangle.obj");
	gameObjects[2].translateAll(mat4::translationMatrix(vec3(0.5f, 0.5f, 0.4f)), 0);
	gameObjects[2].rotateAll(qtrn::qFromAngleAxis(135, vec3(0, 0, 1)), 0);
	gameObjects[2].scaleAll(mat4::scaleMatrix(vec3(sqrt(2), sqrt(2), 0.4f)), 0);
	//above state
	gameObjects[2].translateAll(mat4::translationMatrix(vec3(0.5f, 0.5f, 6.4f)), 1);
	gameObjects[2].rotateAll(qtrn::qFromAngleAxis(135, vec3(0, 0, 1)), 1);
	gameObjects[2].scaleAll(mat4::scaleMatrix(vec3(sqrt(2), sqrt(2), 0.4f)), 1);
	//above end state
	gameObjects[2].translateAll(mat4::translationMatrix(vec3(1.5f, -1.5f, 6.4f)), 2);
	gameObjects[2].rotateAll(qtrn::qFromAngleAxis(-135, vec3(0, 0, 1)), 2);
	gameObjects[2].scaleAll(mat4::scaleMatrix(vec3(sqrt(2), sqrt(2), 0.4f)), 2);
	//end state
	gameObjects[2].translateAll(mat4::translationMatrix(vec3(1.5f, -1.5f, 0.4f)), 3);
	gameObjects[2].rotateAll(qtrn::qFromAngleAxis(-135, vec3(0, 0, 1)), 3);
	gameObjects[2].scaleAll(mat4::scaleMatrix(vec3(sqrt(2), sqrt(2), 0.4f)), 3);

	gameObjects[2].canAnimate = true;

	//big triangles
	//initial state
	gameObjects[3] = GameObject::loadMesh("./src/meshes/triangle.obj");
	gameObjects[3].translateAll(mat4::translationMatrix(vec3(-0.7125f, -0.7125f, 0.55f)), 0);
	gameObjects[3].rotateAll(qtrn::qFromAngleAxis(45, vec3(0, 0, 1)), 0);
	gameObjects[3].scaleAll(mat4::scaleMatrix(vec3(2, 2, 0.55f)), 0);
	//above state
	gameObjects[3].translateAll(mat4::translationMatrix(vec3(-0.7125f, -0.7125f, 8.55f)), 1);
	gameObjects[3].rotateAll(qtrn::qFromAngleAxis(45, vec3(0, 0, 1)), 1);
	gameObjects[3].scaleAll(mat4::scaleMatrix(vec3(2, 2, 0.55f)), 1);
	//above end state
	gameObjects[3].translateAll(mat4::translationMatrix(vec3(-1.0f, 0.0f, 8.55f)), 2);
	gameObjects[3].rotateAll(qtrn::qFromAngleAxis(-90, vec3(0, 0, 1)), 2);
	gameObjects[3].scaleAll(mat4::scaleMatrix(vec3(2, 2, 0.55f)), 2);
	//end state
	gameObjects[3].translateAll(mat4::translationMatrix(vec3(-1.0f, 0.0f, 0.55f)), 3);
	gameObjects[3].rotateAll(qtrn::qFromAngleAxis(-90, vec3(0, 0, 1)), 3);
	gameObjects[3].scaleAll(mat4::scaleMatrix(vec3(2, 2, 0.55f)), 3);

	gameObjects[3].canAnimate = true;

	//initial state
	gameObjects[4] = GameObject::loadMesh("./src/meshes/triangle.obj");
	gameObjects[4].translateAll(mat4::translationMatrix(vec3(0.70f, -2.125f, 0.70f)), 0);
	gameObjects[4].rotateAll(qtrn::qFromAngleAxis(-135, vec3(0, 0, 1)), 0);
	gameObjects[4].scaleAll(mat4::scaleMatrix(vec3(2, 2, 0.70f)), 0);
	//above state
	gameObjects[4].translateAll(mat4::translationMatrix(vec3(0.70f, -2.125f, 10.70f)), 1);
	gameObjects[4].rotateAll(qtrn::qFromAngleAxis(-135, vec3(0, 0, 1)), 1);
	gameObjects[4].scaleAll(mat4::scaleMatrix(vec3(2, 2, 0.70f)), 1);
	//above end state
	gameObjects[4].translateAll(mat4::translationMatrix(vec3(0.0f, 1.0f, 10.70f)), 2);
	gameObjects[4].rotateAll(qtrn::qFromAngleAxis(-180, vec3(0, 0, 1)), 2);
	gameObjects[4].scaleAll(mat4::scaleMatrix(vec3(2, 2, 0.70f)), 2);
	//end state
	gameObjects[4].translateAll(mat4::translationMatrix(vec3(0.0f, 1.0f, 0.70f)), 3);
	gameObjects[4].rotateAll(qtrn::qFromAngleAxis(-180, vec3(0, 0, 1)), 3);
	gameObjects[4].scaleAll(mat4::scaleMatrix(vec3(2, 2, 0.70f)), 3);
	
	gameObjects[4].canAnimate = true;

	//square
	//initial state
	gameObjects[5] = GameObject::loadMesh("./src/meshes/square.obj");
	gameObjects[5].translateAll(mat4::translationMatrix(vec3(1.0f, 2.0f, 0.85f)), 0);
	gameObjects[5].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.85f)), 0);
	//above state
	gameObjects[5].translateAll(mat4::translationMatrix(vec3(1.0f, 2.0f, 12.85f)), 1);
	gameObjects[5].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.85f)), 1);
	//above end state
	gameObjects[5].translateAll(mat4::translationMatrix(vec3(1.0f, 0.0f, 12.85f)), 2);
	gameObjects[5].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.85f)), 2);
	//end state
	gameObjects[5].translateAll(mat4::translationMatrix(vec3(1.0f, 0.0f, 0.85f)), 3);
	gameObjects[5].scaleAll(mat4::scaleMatrix(vec3(1, 1, 0.85f)), 3);

	gameObjects[5].canAnimate = true;

	//parallelogram
	//initial state
	gameObjects[6] = GameObject::loadMesh("./src/meshes/parallelogram.obj");
	gameObjects[6].translateAll(mat4::translationMatrix(vec3(-0.50f, 1.5f, 1.0f)), 0);
	gameObjects[6].rotateAll(qtrn::qFromAngleAxis(90, vec3(0, 0, 1)), 0);
	//above state
	gameObjects[6].translateAll(mat4::translationMatrix(vec3(-0.50f, 1.5f, 15.0f)), 1);
	gameObjects[6].rotateAll(qtrn::qFromAngleAxis(90, vec3(0, 0, 1)), 1);
	//above end state
	gameObjects[6].translateAll(mat4::translationMatrix(vec3(-0.50f, -1.5f, 15.0f)), 2);
	//end state
	gameObjects[6].translateAll(mat4::translationMatrix(vec3(-0.50f, -1.5f, 1.0f)), 3);

	gameObjects[6].canAnimate = true;

	gameObjects[7] = GameObject::loadMesh("./src/meshes/square.obj");
	gameObjects[7].translateSelf(mat4::translationMatrix(vec3(0.0f, 0.0f, -0.01f)), 0);
	gameObjects[7].rotateSelf(qtrn::qFromAngleAxis(45, vec3(0, 0, 1)), 0);
	gameObjects[7].rotateSelf(qtrn::qFromAngleAxis(180, vec3(0, 1, 0)), 0);
	gameObjects[7].scaleSelf(mat4::scaleMatrix(vec3(20, 20, 0.000001f)), 0);

	gameObjects[7].canAnimate = false;

	SceneNode* parent = scene->addNode(nullptr, &gameObjects[7]);
	gameObjects[7].ProjectionMatrix = &ProjectionMatrix;
	gameObjects[7].ViewMatrix = &ViewMatrix;
	gameObjects[7].init(UBO_BP);

	for (int i = 0; i < 7; i++) {
		gameObjects[i].ProjectionMatrix = &ProjectionMatrix;
		gameObjects[i].ViewMatrix = &ViewMatrix;
		gameObjects[i].init(UBO_BP);
		scene->addNode(parent, &gameObjects[i]);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");

	glutTimerFunc(0, GameManager::runAnimation, 0);
}

void GameManager::destroyBufferObjects()
{

	for (int i = 0; i < 9; i++) {
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

void GameManager::runAnimation(int value)
{
	int milliseconds = 20;
	GameManager::scene->runAnimation(milliseconds);
	glutTimerFunc(milliseconds, runAnimation, 0);
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