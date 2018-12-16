#include <GL/glut.h>
#include <cstdlib>
#include <iostream>

float sunX = 350;
bool riseSun = true;


void display();
void init();
void drawGround();
void drawHouse();
void drawSun();

void spinSun(int);

int main(int argc, char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("OpenGL Lab 1");
	glutDisplayFunc(display);
	glutTimerFunc(40, spinSun, 0);
	
	init();
	
	glutMainLoop();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.4, 0.8, 0.6);
	drawGround();
	drawHouse();
	glColor3f(0.9, 0.9, 0.6);
	drawSun();

	glFlush();
}

void init() {
	glClearColor(0.6, 0.8, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-300.0, 300.0, -300.0, 300.0, -300.0, 300.0);
}

void drawGround() {
	glBegin(GL_QUADS);

	glVertex2d(-300, -300);
	glVertex2d(-300, -50);
	glVertex2d(300, -50);
	glVertex2d(300, -300);

	glEnd();
}

void drawHouse() {
	glBegin(GL_QUADS);
		glColor3f(0.5, 0.2, 0.1);
		glVertex2d(-100, 0);
		glVertex2d(-100, -75);
		glVertex2d(0, -75);
		glVertex2d(0, 0);
		
	glEnd();

	glBegin(GL_TRIANGLES);

	glColor3f(0.5, 0.2, 0.4);
	glVertex2d(-120, 0);
	glVertex2d(-50, 55);
	glVertex2d(20, 0);

	glEnd();
}

void drawSun() {
	glPushMatrix();
	glTranslatef(0, 100.0f, 0.0f);

	GLfloat theta;
	GLfloat pi = acos(-1.0);
	GLfloat radius = 40.0f; 
	GLfloat step = 6.0f; 

	glBegin(GL_TRIANGLE_FAN);

	for (GLfloat a = 0.0f; a < 360.0f; a += step) {
		theta = 2.0f * pi * a / 180.0f;
		glVertex2f(radius * cos(theta), radius * sin(theta));
	}

	glEnd();
	
	glPopMatrix();
}

void spinSun(int value) {
	if (riseSun) 
		glClearColor(0.1, 0.1, 0.8, 1.0);
	else 
		glClearColor(0.6, 0.8, 1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT);

	if (sunX > -350) sunX -= 3;
	else {
		sunX = 350;
		riseSun = !riseSun;
	}

	if (riseSun) glColor3f(0.1, 0.3, 0.2); 
	else glColor3f(0.4, 0.8, 0.6);
	drawGround();
	drawHouse();

	glPushMatrix();
	glTranslated(sunX, 100, 0);
	if (riseSun) glColor3f(0.7, 0.9, 1.0);
	else glColor3f(0.9, 0.9, 0.7);
	drawSun();
	glPopMatrix();

	glFlush();
	glutTimerFunc(40, spinSun, 0);
}