#include <glut.h>
#include "Scene.h"
#include "Field.h"
#include "House.h"
#include "Sun.h"

int main(int argc, char * argv[]) {
	Scene scene;
	scene.init(&argc, argv);
	Field field;
	scene.addElement(&field);
	House house;
	scene.addElement(&house);
	Sun sun(&scene);
	scene.addElement(&sun);
	scene.start();
}