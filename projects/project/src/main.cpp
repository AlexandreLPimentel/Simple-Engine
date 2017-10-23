#include "GameManager.h"
#include "test\testRunner.h"

AbstractGameManager* game;

void timer(int value)
{
	game->timer(value);
	glutTimerFunc(1000, timer, 0);
}

void keyTimer(int value)
{
	game->keyTimer(value);
	glutTimerFunc(10, keyTimer, 0);
}

void cleanup() {
	game->cleanup();
}

void display() {
	game->display();
}

void idle() {
	game->idle();
}

void reshape(int w, int h) {
	game->reshape(w, h);
}

void parseKeyboardUpEvent(unsigned char key, int x, int y) {
	game->keyboard(key, x, y, true);
}

void parseKeyboardDownEvent(unsigned char key, int x, int y) {
	game->keyboard(key, x, y, false);
}

void parseMouseEvent(int button, int state, int x, int y) {
	game->mouse(button, state, x, y);
}

void parseMouseMovent(int x, int y) {
	game->mouseMovement(x, y);
}

void setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardUpFunc(parseKeyboardUpEvent);
	glutKeyboardFunc(parseKeyboardDownEvent);
	glutMouseFunc(parseMouseEvent);
	glutPassiveMotionFunc(parseMouseMovent);
	glutTimerFunc(0, timer, 0);
	glutTimerFunc(0, keyTimer, 0);
}

void init(int argc, char* argv[])
{
	game->init(argc, argv);
	setupCallbacks();
}

int main(int argc, char* argv[])
{
	game = new GameManager();
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
	std::cin.get();
	return 0;
};