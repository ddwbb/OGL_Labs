#include "Field.h"



Field::Field() {
	vertexes = new GLfloat[8];
	GLfloat arr[] = { -400, -300, -400, -40, 400, -40, 400, -300 };
	for (int i = 0; i < 8; i++) {
		vertexes[i] = arr[i];
	}
}

Field::Field(GLfloat arr[]) {
	vertexes = new GLfloat[8];
	for (int i = 0; i < 8; i++) {
		vertexes[i] = arr[i];
	}
}


Field::~Field()
{
}

void Field::render() {
	init();
	GLushort ids[] = { 0, 1, 2, 3 };
	glColor4f(color[0], color[1], color[2], transparent);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, ids);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Field::init() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 2 * sizeof(GLfloat), vertexes);
	GLfloat fieldColor[] = { 0.4, 0.7, 0.4 };
	setColor(fieldColor);
}