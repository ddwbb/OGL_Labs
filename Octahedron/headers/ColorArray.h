#pragma once

#ifndef COLOR_ARRAY
#define COLOR_ARRAY
#include "config.h"

//Для доступа к типу GLfloat
#include <GL/glut.h> 

class ColorArray {
	int size;
	GLfloat * array;

	void copy_values(GLfloat *);
public:
	ColorArray();
	ColorArray(int);
	ColorArray(int, GLfloat *);
	~ColorArray();
	
	operator GLfloat *();

	int length();
	void set_color(int);
	void set_color(GLfloat *);
	void reset();
};

//Костыльная функция подсчета размера массива
int array_size(GLfloat *);

#endif