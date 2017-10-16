#include "GameManager.h"
#include "test\testRunner.h"

AbstractGameManager* game;

void timer(int value)
{
	game->timer(value);
	glutTimerFunc(1000, timer, 0);
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

void setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
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