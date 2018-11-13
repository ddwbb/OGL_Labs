#include "Sun.h"
#include <math.h>
#include <cstdio>

Sun::Sun() {
	angle = 0;
}

Sun::Sun(Scene * parent) {
	color[0] = 1.0;
	color[1] = 0.9;
	color[2] = 0.7;

	angle = 0;
	this->parent = parent;
}


Sun::~Sun()
{
}

void Sun::render() {
	GLfloat theta;
	GLfloat pi = acos(-1.0);
	GLfloat radius = 40.0f;
	GLfloat step = 6.0f;

	glBegin(GL_TRIANGLE_FAN);

	glColor3f(color[0], color[1], color[2]);
	for (GLfloat a = 0.0f; a < 360.0f; a += step) {
		theta = 2.0f * pi * a / 180.0f;
		glVertex2f(radius * cos(theta), radius * sin(theta));
	}

	glEnd();
}

void Sun::move() {
	glPushMatrix();

	glTranslatef(500 * cos(angle), 400 * sin(angle) - 150, 0);
	angle += 0.05;
	if (angle * 180 / 3.14 >= 180) {
		angle = 0;
		parent->changeDayState();
	}
	render();

	glPopMatrix();
}

void Sun::setDayColor() {
	color[0] = 1.0;
	color[1] = 0.9;
	color[2] = 0.7;
}

void Sun::setNightColor() {
	color[0] = 0.7;
	color[1] = 0.9;
	color[2] = 1.0;
}