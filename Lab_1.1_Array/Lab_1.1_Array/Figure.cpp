#include "Figure.h"



Figure::Figure() {
	color[0] = color[1] = color[2] = 0;
	transparent = 1;
}


Figure::~Figure() {

}

void Figure::setColor(GLfloat arr[3]) {
	for (int i = 0; i < 3; i++) {
		color[i] = arr[i];
	}
}

void Figure::move() {
	render();
}

void Figure::setDayColor() {

}

void Figure::setNightColor() {

}