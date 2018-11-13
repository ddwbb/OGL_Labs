#pragma once
#include "Figure.h"
#include "Scene.h"

class Sun : public Figure {
	GLfloat angle;
	Scene * parent;
public:
	Sun();
	Sun(Scene * parent);
	~Sun();

	void render();
	void move();
	void setDayColor();
	void setNightColor();
};

