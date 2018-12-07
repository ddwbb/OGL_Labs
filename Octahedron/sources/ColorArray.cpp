#include "../headers/ColorArray.h"

ColorArray::ColorArray() {
	size = 0;
	array = nullptr;
}

ColorArray::ColorArray(int n) {
	size = n;
	array = new GLfloat[n];
}

ColorArray::ColorArray(int n, GLfloat * colors) {
	size = n;
	array = new GLfloat[n];
	copy_values(colors);
}

ColorArray::~ColorArray() {
	size = 0;
	if (array) delete array;
}

void ColorArray::copy_values(GLfloat * colors) {
	int colors_length = array_size(colors);
	if (size != colors_length) {
		delete array;
		size = colors_length;
		array = new GLfloat[size];
	}
	for (int i = 0; i < size; i++) {
		array[i] = colors[i];
	}
}

ColorArray::operator GLfloat *() {
	return array;
}

int ColorArray::length() {
	return size;
}

void ColorArray::set_color(int color_id) {
	size = 9;
	reset();

	switch (color_id) {
	case RED:
		array[0] = array[3] = array[6] = 1;
		break;
	case ORANGE:
		array[0] = array[3] = array[6] = 0.7;
		array[1] = array[4] = array[7] = 0.3;
		break;
	case YELLOW:
		array[0] = array[3] = array[6] = 1;
		array[1] = array[4] = array[7] = 1;
		break;
	case GREEN:
		array[1] = array[4] = array[7] = 1;
		break;
	case LIGHT_BLUE:
		array[1] = array[4] = array[7] = 1;
		array[2] = array[5] = array[8] = 1;
		break;
	case DARK_BLUE:
		array[2] = array[5] = array[8] = 0.7;
		break;
	case PURPLE:
		array[0] = array[3] = array[6] = 1;
		array[2] = array[5] = array[8] = 1;
		break;
	case MIXED:
		array[0] = array[4] = array[8] = 1;
		break;
	default:
		for (int i = 0; i < 9; i++)
			array[i] = 1;
		break;
	}
}

void ColorArray::set_color(GLfloat * colors) {
	copy_values(colors);
}

void ColorArray::reset() {
	if (!size) array = nullptr;
	else {
		if (array == nullptr) array = new GLfloat[size];
		for (int i = 0; i < size; i++) {
			array[i] = 0;
		}
	}
}

int array_size(GLfloat * colors) {
	int colors_length = sizeof(colors) / sizeof(GLfloat);
	if (colors_length != 1) {
		return colors_length;
	}
	colors_length = 0;
	try {
		for (int i = 0; ; i++) {
			colors[i];
			colors_length = i;
		}
	}
	catch (...) {
		return colors_length + 1;
	}
}