#include "../headers/Scene.h"

Scene::Scene() {
	instance = this;
	initialized = false;
	full_screen = FULL_SCREEN_VIEW;

	texturing = TEXTURE_SINGLE;
	texture_count = texture_paths.size();
	texture_names = new GLuint[texture_count];
	texture_images = new AUX_RGBImageRec *[texture_count];

	slice_count = SLILCE_COUNT_DEFAULT;

	slicing = false;
	alpha = ALPHA_DEFAULT;

	blending = BLENDING_DEFAULT;

	light_disabled = LIGHTING_DEFAULT;
	lighting = LIGHTING_DEFAULT;
	light_angle = LIGHT_ANGLE_DEFAULT;
	light_speed = LIGHT_SPEED_DEFAULT;
	light_distance = LIGHT_DISTANCE_DEFAULT;

	triangle_angle = TRIANGLE_ANGLE_DEFAULT;
	triangle_speed = TRIANGLE_SPEED_DEFAULT;
	triangle_rotating = TRIANGLE_ROTATING_DEFAULT;

	octahedron_angle = OCTAHEDRON_ANGLE_DEFAULT;
	octahedron_speed = OCTAHEDRON_SPEED_DEFAULT;
	octahedron_aspect = OCTAHEDRON_ASPECT_DEFAULT;
}

Scene::~Scene() {
	if (texture_names) delete texture_names;
	if (texture_images) delete texture_images;
}

//Iinitialize
void Scene::init(int * argc, char ** argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	if (full_screen) {
		glutCreateWindow("OpenGL Octahedron");
		glutFullScreen();
	}
	else {
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(992, 558);
		glutCreateWindow("OpenGL Octahedron");
	}
	

	glutDisplayFunc(callback_display);
	glutKeyboardFunc(callback_key_press);
	glutTimerFunc(40, callback_animation, 0);

	init_view();
	init_material();
	init_texture();
	init_sliced_octahedron();

	initialized = true;
}

void Scene::init_view() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)16 / 9, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 30, 400, 0, 0, 0, 0, 400, -30);
}

void Scene::init_light() {
	GLfloat position[] = { 0, 0, 0, 1 };
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat diffuse[] = { 1, 1, 1, 1 };

	if (!lighting) {
		if (light_disabled) return;
			glDisable(GL_LIGHT0);
			light_disabled = true;
	} else {
		if (light_disabled) {
			light_disabled = false;
			glEnable(GL_LIGHT0);
		}
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	}
}

void Scene::init_texture() {
	glGenTextures(texture_count, texture_names);
	for (int i = 0; i < texture_count; i++) {
		glBindTexture(GL_TEXTURE_2D, texture_names[i]);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		texture_images[i] = auxDIBImageLoad(texture_paths[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_images[i]->sizeX, texture_images[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_images[i]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
}

void Scene::init_material() {
	GLfloat ambient[] = { 0.02, 0.02, 0.02, 1 };
	GLfloat diffuse_front[] = { 1, 1, 1, 1 };
	GLfloat diffuse_back[] = { 0.2, 0.2, 0.2, 1 };

	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_front);
	glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse_back);
}

//
void Scene::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_octahedron();
	draw_sphere();
	glRotatef(90, 0, 1, 0);
	glFlush();
}

void Scene::animation(int value) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_sphere();
	
	if (octahedron_angle + octahedron_speed > 360 || octahedron_angle + octahedron_speed < -360) {
		octahedron_angle = 0;
	}
	else {
		octahedron_angle += octahedron_speed;
	}

	glPushMatrix();
		glRotatef(octahedron_angle, 0, 1, 0);
		draw_octahedron();
	glPopMatrix();
	glFlush();

	glutTimerFunc(40, callback_animation, 0);
}

void Scene::key_press(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS);
		break;
	case 'q':
		octahedron_aspect += OCTAHEDRON_ASPECT_DIFFERENCE_VALUE;
		break;
	case 'e':
		if (octahedron_aspect - OCTAHEDRON_ASPECT_DIFFERENCE_VALUE >= 0) 
			octahedron_aspect -= OCTAHEDRON_ASPECT_DIFFERENCE_VALUE;
		break;
	case 'a':
		glRotatef(CAMERA_ROTATE_ANGLE_VALUE, 0, 1, 0);
		break;
	case 'd':
		glRotatef(-CAMERA_ROTATE_ANGLE_VALUE, 0, 1, 0);
		break;
	case ' ':
		lighting = !lighting;
		break;
	case 'w':
		if (light_distance + LIGHT_DISTANCE_DIFFERENCE_VALUE <= 0)
			light_distance += LIGHT_DISTANCE_DIFFERENCE_VALUE;
		break;
	case 's':
		light_distance -= LIGHT_DISTANCE_DIFFERENCE_VALUE;
		break;
	case 'c':
		triangle_rotating = true;
		triangle_speed += TRIANGLE_SPEED_VALUE;
		break;
	case 'v':
		triangle_rotating = true;
		triangle_speed -= TRIANGLE_SPEED_VALUE;
		break;
	case 'g':
		triangle_rotating = false;
		break;
	case 'G':
		triangle_rotating = false;
		triangle_angle = 0;
		triangle_speed = 0;
		break;
	case ',':
		light_speed -= LIGHT_SPEED_VALUE;
		break;
	case '.':
		light_speed += LIGHT_SPEED_VALUE;
		break;
	case 'R':
		blending = BLENDING_DEFAULT;
		slicing = SLICING_DEFAULT;
		lighting = LIGHTING_DEFAULT;
		light_angle = LIGHT_ANGLE_DEFAULT;
		light_speed = LIGHT_SPEED_DEFAULT;
		light_distance = LIGHT_DISTANCE_DEFAULT;
		triangle_angle = TRIANGLE_ANGLE_DEFAULT;
		triangle_speed = TRIANGLE_SPEED_DEFAULT;
		triangle_rotating = TRIANGLE_ROTATING_DEFAULT;
		octahedron_angle = OCTAHEDRON_ANGLE_DEFAULT;
		octahedron_speed = OCTAHEDRON_SPEED_DEFAULT;
		octahedron_aspect = OCTAHEDRON_ASPECT_DEFAULT;
		break;
	case '1':
		octahedron_speed -= OCTAHEDRON_SPEED_VALUE;
		break;
	case '2':
		octahedron_speed += OCTAHEDRON_SPEED_VALUE;
		break;
	case 't':
		if (texture_count && texturing == TEXTURE_SINGLE)
			texturing = TEXTURE_NONE;
		else
			texturing++;
		break;
	case '-': 
		alpha = (alpha - ALPHA_DIFFERENCE_VALUE <= 0) ? 0 : alpha - ALPHA_DIFFERENCE_VALUE;
		break;
	case '=':
		alpha = (alpha + ALPHA_DIFFERENCE_VALUE >= 1) ? 1 : alpha + ALPHA_DIFFERENCE_VALUE;
		break;
	case 'b':
		blending = !blending;
		break;
	case 'l':
		if (slicing == SLICING_TRANSPARENT)
			slicing = SLICING_OFF;
		else
			slicing++;
		break;
	default:
		break;
	}
}

//Drawing
void Scene::draw_octahedron() {
	switch(slicing){
		case SLICING_COMMON:
			glCallList(octahedron_list[0]);
			break;
		case SLICING_TRANSPARENT:
			glCallList(octahedron_list[1]);
			break;
		default:
			glPushMatrix();
			for (int i = 0; i < 8; i++) {
				if (texturing == TEXTURE_SINGLE) draw_triangle(TEXTURE_ID_DEFAULT);
				else draw_triangle(i);
				glRotatef(90 * (i + 1), 0, 1, 0);
				if (i == 3) glRotatef(180, 0, 0, 1);
			}
			glPopMatrix();
			break;
		}
}

void Scene::draw_triangle(int color) {
	GLfloat vertexes[] = {
		-40, 0, 40,
		40, 0, 40,
		0, 70, 0
	};

	GLubyte indeces[] = { 0, 1, 2 };
	ColorArray color_array;

	glEnableClientState(GL_VERTEX_ARRAY);

	if (!texturing) {
		glEnableClientState(GL_COLOR_ARRAY);
		color_array.set_alpha(alpha);
		color_array.set_color(color);
		glColorPointer(4, GL_FLOAT, 0, color_array);
	}
	else {
		GLfloat texture_coord[] = {
			0, 0,
			1, 0,
			0.5, 1
		};
		glColor4f(1, 1, 1, alpha);
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, texture_coord);
		if (color >= texture_count) color = texture_count - 1;
		glBindTexture(GL_TEXTURE_2D, texture_names[color]);
	}

	if (blending) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);

	}

	glVertexPointer(3, GL_FLOAT, 0, vertexes);
	glNormal3f(0, 40, 70);

	if (triangle_angle + triangle_speed > 360 || triangle_angle + triangle_speed < -360) {
		triangle_angle = 0;
		if (!triangle_rotating)
			triangle_speed = 0;
	}
	else {
		triangle_angle += triangle_speed;
	}

	glPushMatrix();
		glTranslatef(0, 40 * octahedron_aspect, 70 * octahedron_aspect);
		glPushMatrix();
			glTranslatef(0, 18.5, 0);
		glPopMatrix();
		glRotatef(triangle_angle, 0, 40, 70);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indeces);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);

	if (!texturing)
		glDisableClientState(GL_COLOR_ARRAY);
	else {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void Scene::init_sliced_octahedron() {
	octahedron_list[0] = glGenLists(1);
	slicing = SLICING_COMMON;
	glNewList(octahedron_list[0], GL_COMPILE_AND_EXECUTE);
		glPushMatrix();
		for (int i = 0; i < 8; i++) {
			init_sliced_triangles(i);
			glRotatef(90 * (i + 1), 0, 1, 0);
			if (i == 3) glRotatef(180, 0, 0, 1);
		}
		glPopMatrix();
	glEndList();
	slicing = SLICING_TRANSPARENT;
	octahedron_list[1] = glGenLists(1);
	glNewList(octahedron_list[1], GL_COMPILE_AND_EXECUTE);
	glPushMatrix();
	for (int i = 0; i < 8; i++) {
		init_sliced_triangles(i);
		glRotatef(90 * (i + 1), 0, 1, 0);
		if (i == 3) glRotatef(180, 0, 0, 1);
	}
	glPopMatrix();
	glEndList();
}

void Scene::init_sliced_triangles(int color) {
	GLfloat width_step = (GLfloat)20 / (GLfloat)(slice_count);
	GLfloat height_step = (GLfloat)35 / (GLfloat)(slice_count);
	ColorArray color_array;
		if (slicing == SLICING_TRANSPARENT) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glDepthMask(GL_FALSE);
			color_array.set_alpha(alpha);
		}
	color_array.set_color(color);
	glBegin(GL_QUADS);
		glColor4fv(color_array);
		glNormal3f(0, 40, -70);
		for (int i = 1; i < slice_count * 2; i += 2) {
			glVertex3f(-40 + i * width_step, 0 + i * height_step, 40 - i * width_step);
			glVertex3f(-40 + (i + 1) * width_step, 0 + (i + 1) * height_step, 40 - (i + 1) * width_step);
			glVertex3f(40 - (i + 1) * width_step, 0 + (i + 1) * height_step, 40 - (i + 1) * width_step);
			glVertex3f(40 - i * width_step, 0 + i * height_step, 40 - i * width_step);
		}
	glEnd();
		if (slicing == SLICING_TRANSPARENT) {
			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);
		}
}

void Scene::draw_sphere() {
	glPushMatrix();
	glPushAttrib(GL_LINE_WIDTH);
		if (light_angle + light_speed > 360 || light_angle + light_speed < -360) {
			light_angle = 0;
		}
		else {
			light_angle += light_speed;
		}
		glRotatef(light_angle, 0, 1, 0);
		glPushMatrix();
			glTranslatef(0, 0, light_distance);
			init_light();
			if (lighting) {
				glLineWidth(4);
				glColor3f(1, 1, 0);
				glutWireSphere(8, 8, 8);
			}
		glPopMatrix();
	glPopAttrib();
	glPopMatrix();
}

//Start
void Scene::start() {
	if (initialized) {
		print_instruction();
		glutMainLoop();
	} else {
		cout << "Not initialized" << endl;
		return;
	}
}

void print_instruction() {
	cout << "Keys values:" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "q - Spread Octahedron's faces" << endl;
	cout << "e - Push apart Octahedron's faces" << endl;
	cout << "d - Rotate scene left" << endl;
	cout << "a - Rotate scene right" << endl;
	cout << "c - Rotate Octahedron's faces left" << endl;
	cout << "v - Rotate Octahedron's faces right" << endl;
	cout << "g - No more rotate Octahedron's faces after full circle" << endl;
	cout << "G - Set Octahedron's faces without rotating" << endl;
	cout << "R - Reset Scene" << endl;
	cout << ", - Rotate light right" << endl;
	cout << ". - Rotate light left" << endl;
	cout << "SPACE - light ON/OFF" << endl;
	cout << "l - Slice Octahedron" << endl;
	cout << "1 - Rotate Octahedron right" << endl;
	cout << "2 - Rotate Octahedron left" << endl;
	cout << "t - Faces mod: Colors/Single Texture/Few Textures" << endl;
	cout << "w - Move Light to center" << endl;
	cout << "s - Move Light from center" << endl;
	cout << "b - Blending ON/OFF" << endl;
	cout << "ESC - Exit application" << endl;
}

//Callback Functions
void Scene::callback_display() {
	instance->display();
}

void Scene::callback_key_press(unsigned char key, int x, int y) {
	instance->key_press(key, x, y);
}

void Scene::callback_animation(int value) {
	instance->animation(value);
}