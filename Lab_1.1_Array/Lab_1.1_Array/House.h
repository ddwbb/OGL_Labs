#pragma once
#include "Figure.h"
class House : public Figure {

	void renderHome();
	void renderRoof();
public:
	House();
	~House();

	void render();
};

