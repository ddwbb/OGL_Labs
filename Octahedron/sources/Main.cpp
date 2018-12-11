#include "../headers/Scene.h"

int main(int argc, char * argv[]) {
	Scene scene;
	scene.init(&argc, argv);
	scene.start();
}
