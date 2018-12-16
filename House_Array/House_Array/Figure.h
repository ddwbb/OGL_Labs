#pragma once
#include <GL/glut.h>

using namespace std;

class Figure {
protected:
	GLfloat color[3];
	GLfloat transparent;
	GLfloat * vertexes;
	bool night;
public:
	Figure();
	virtual ~Figure();

	void setColor(GLfloat arr[3]);
	virtual void render() = 0;
	virtual void move();
	virtual void setDayColor();
	virtual void setNightColor();
};

