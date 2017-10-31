///////////////////////////////////////////////////////////////////////
//
// Using quaternions to rotate in 3D.
//
// Assignment: 1. Create a class for Quaternions.
//             2. Create a scene with a camera rotating around an 
//                object at the origin and pointing towards it. 
//                Do NOT use "gluLookAt" to create the ViewMatrix, 
//                use rotation matrices!
//             3. Gimbal lock mode ON: use Translation + Rotation 
//                matrices (e.g. Euler angles, Rodrigues’ formula).
//             4. Gimbal lock mode OFF: use Quaternions to produce a 
//                transformation matrix and avoid gimbal lock.
//             5. Switch between modes by pressing the 'g' key.
//
// (c) 2013-17 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////


#include "GameManager.h"

#define CAPTION "Hello Modern 3D World"

#define VERTICES 0
#define COLORS 1
#define OFFSET 2.0f

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
	if (!(d || a || w || s || r || l)) {
		return;
	}
	camera.move(a * OFFSET - d * OFFSET, w * OFFSET - s * OFFSET, 0, 0, 0);
	
	//old
	//camera.move(d * OFFSET - a * OFFSET, r * OFFSET - l * OFFSET, w * OFFSET - s * OFFSET, 0, 0);
	//*ViewMatrix *= mat4::translationMatrix(vec3(d * OFFSET - a * OFFSET, w * OFFSET - s * OFFSET, r * OFFSET - l * OFFSET));
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
	case 'g':
		g = !g;
		if (g) {
			camera.changeMode();
		}
		break;
	case 'w':
		if (w != pressed) {
			//cout << "w is " << (pressed ? "now pressed" : "no longer pressed") << endl;
		}
		w = pressed;
		break;
	case 's':
		if (s != pressed) {
			//cout << "s is " << (pressed ? "now pressed" : "no longer pressed") << endl;
		}
		s = pressed;
		break;
	case 'a':
		if (a != pressed) {
			//cout << "a is " << (pressed ? "now pressed" : "no longer pressed") << endl;
		}
		a = pressed;
		break;
	case 'd':
		if (d != pressed) {
			//cout << "d is " << (pressed ? "now pressed" : "no longer pressed") << endl;
		}
		d = pressed;
		break;
	case 'q':
		exit(0);
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
		camera.move(0, 0, 0, mouseX - x, mouseY - y);
	}
	if (x > 3 * WinX / 4 || x < WinX / 4 ) {
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
	ProjectionMatrixOrtho = mat4::ortho((float)-w / 100, (float)w / 100, (float)h / 100, (float)-h / 100, 1, 50);
	ProjectionMatrixPerspective = mat4::perspective(25, (float)w / h, 1, 50);
}

void GameManager::init(int argc, char* argv[]) {
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	createShaderProgram();
	createBufferObjects();
	camera = Camera(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0));
	ViewMatrix = &(camera.ViewMatrix);
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