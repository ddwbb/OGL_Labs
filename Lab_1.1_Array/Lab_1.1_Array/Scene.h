#pragma once

#include <glut.h>
#include <list>
#include "Figure.h"

using namespace std;

class Scene {
	int width;
	int height;

	bool night;

	list<Figure *> elements;

	static void callbackRender();
	static void callbackAnimation(int);
	static void callbackResize(int, int);

public:
	Scene();
	~Scene();

	void init(int *, char * ar[]);
	void render();
	void resize(int, int);
	void animation();
	void start();
	void addElement(Figure *);
	void changeDayState();
};

static Scene * instance;
