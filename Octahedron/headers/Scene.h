#pragma once

#include <GL/glut.h>
#include <glaux.h>
#include <cstdio>
#include <iostream>

#include "config.h"
#include "ColorArray.h"

using namespace std;

class Scene {
	bool initialized;
	bool lighting;
	bool light_disabled;
	bool triangle_rotating;
	bool full_screen;
	bool blending;
	int slicing;

	int texturing;
	int texture_count;
	int slice_count;

	GLfloat alpha;
	GLfloat light_angle;
	GLfloat light_speed;
	GLfloat light_distance;
	GLfloat triangle_angle;
	GLfloat triangle_speed;
	GLfloat octahedron_angle;
	GLfloat octahedron_speed;
	GLfloat octahedron_aspect;

	GLuint octahedron_list[2];
	GLuint * texture_names;
	AUX_RGBImageRec ** texture_images;

	void init_view();
	void init_light();
	void init_texture();
	void init_material();
	
	static void callback_display();
	static void callback_animation(int);
	static void callback_key_press(unsigned char, int, int);
public:
	Scene();
	~Scene();

	void init(int *, char **);
	void display();
	void animation(int);
	void key_press(unsigned char, int, int);
	void start();

	void draw_octahedron();
	void draw_triangle(int);
	void draw_sphere();

	void init_sliced_octahedron();
	void init_sliced_triangles(int);
};

static Scene * instance = nullptr;

void print_instruction(); 