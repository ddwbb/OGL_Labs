#include "House.h"



House::House() {
	
}


House::~House()
{
}

void House::render() {
	renderHome();
	renderRoof();
}

void House::renderHome() {
	GLfloat houseColor[] = { 0.2, 0.3, 0.6 };
	setColor(houseColor);
	GLfloat house[] = { -70, -70, -70, -10, 20, -10, 20, -70 };
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 2 * sizeof(GLfloat), house);
	GLuint ids[] = { 0, 1, 2, 3 };
	glColor3f(color[0], color[1], color[2]);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, ids);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void House::renderRoof() {
	GLfloat roofColor[] = { 0.5, 0.3, 0.2 };
	setColor(roofColor);
	GLfloat house[] = { -90, -10, -25, 20, 40, -10 };
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 2 * sizeof(GLfloat), house);
	GLuint ids[] = { 0, 1, 2 };
	glColor3f(color[0], color[1], color[2]);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, ids);
	glDisableClientState(GL_VERTEX_ARRAY);
}