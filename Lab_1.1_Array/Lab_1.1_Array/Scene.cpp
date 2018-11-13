#include "Scene.h"



Scene::Scene() : width(800), height(600), night(false) {
	instance = this;
}


Scene::~Scene() {

}

void Scene::init(int * argc, char * argv[]) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("OpenGL");

	::glutDisplayFunc(callbackRender);
	::glutReshapeFunc(callbackResize);
	::glutTimerFunc(40, callbackAnimation, 0);

	glClearColor(0.7, 0.9, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(-(GLdouble)(width / 2.0), (GLdouble)(width / 2.0), -(GLdouble)(height / 2.0), (GLdouble)(height / 2.0));
}

void Scene::start() {
	glutMainLoop();
}

void Scene::addElement(Figure * figure) {
	elements.push_back(figure);
}

void Scene::changeDayState() {
	night = !night;
}

void Scene::callbackAnimation(int value) {
	instance->animation();
	::glutTimerFunc(40, callbackAnimation, 0);
}

void Scene::callbackRender() {
	instance->render();
}

void Scene::callbackResize(int width, int height) {
	instance->resize(width, height);
}

void Scene::resize(int width, int height) {
	this->width = width;
	if (!height)
		height = 1;
	this->height = height;

	glViewport(0, 0, this->width, this->height); 
}

void Scene::render() {
	if (!night)
		glClearColor(0.7, 0.9, 1.0, 1.0);
	else 
		glClearColor(0.1, 0.2, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (list<Figure *>::iterator it = elements.begin(); it != elements.end(); it++) {
		Figure * element = *it;
		if (night)
			element->setNightColor();
		else
			element->setDayColor();
		element->render();
	}

	glFlush();
}

void Scene::animation() {
	if (!night)
		glClearColor(0.7, 0.9, 1.0, 1.0);
	else
		glClearColor(0.1, 0.2, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (list<Figure *>::iterator it = elements.begin(); it != elements.end(); it++) {
		Figure * element = *it;
		if (night)
			element->setNightColor();
		else
			element->setDayColor();
		element->move();
	}

	glFlush();
}