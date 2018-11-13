#pragma once
#include "Figure.h"
class Field : public Figure {
	void init();
public:
	Field();
	Field(GLfloat arr[]);
	~Field();

	void render();
};

