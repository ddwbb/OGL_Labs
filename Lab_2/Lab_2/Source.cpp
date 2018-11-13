#include <glut.h>

#include <cstdlib>
#include <cstdio>

GLfloat aspect = 0.4;
GLfloat angle = 0;
GLfloat light_z = -1000;

void init(int * argc, char * argv[]);
void display();
void key_press(unsigned char, int, int);
void animation(int);
void draw_oct();
void draw_oct_face(GLfloat * v);
void draw_sphere();
void light_init();

int main(int argc, char * argv[]) {
	init(&argc, argv);
	glutMainLoop();
}

void init(int * argc, char * argv[]) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("OpenGL Lab_2");
	glutFullScreen();
	
	glutDisplayFunc(display);
	glutKeyboardFunc(key_press);
	glutTimerFunc(40, animation, 0);

	glEnable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (GLdouble)16 / 9, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-800, 800, -450, 450, 450, 450);
	gluLookAt(0, 30, 400, 0, 0, 0, 0, 400, -30);

	GLfloat mat_spec[] = {0, 0, 0, 0};
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
	//glMaterialfv(GL_BACK, GL_DIFFUSE, mat_spec);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	light_init();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//light_init();
	draw_oct();
	draw_sphere();
	glRotatef(90, 0, 1, 0);

	glFlush();
}

void animation(int value) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	light_init();
	draw_sphere();
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
	draw_oct();
	glPopMatrix();
	glFlush();

	if (angle * 3.14 / 180 >= 360) angle = 0;
	else angle++;

	glutTimerFunc(40, animation, 0);
}

void key_press(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS);
		break;
	case 'q':
		aspect += 0.005;
		//display();
		break;
	case 'e':
		if (aspect - 0.005 > 0) aspect -= 0.005;
		//display();
		break;
	default:
		light_z += 10;
		break;
	}
}

void draw_oct() {
	GLfloat top_face[] = {
		1, 0, 0, -40, 0, 40,
		1, 0, 0, 40, 0, 40,
		1, 0, 0, 0, 70, 0
	};

	GLfloat top_right[] = {
		1, 0.6, 0, 40, 0, 40,
		1, 0.6, 0, 40, 0, -40,
		1, 0.6, 0, 0, 70, 0
	};

	GLfloat top_left[] = {
		1, 1, 0, -40, 0, 40,
		1, 1, 0, -40, 0, -40,
		1, 1, 0, 0, 70, 0
	};

	GLfloat top_back[] = {
		0, 1, 0, 40, 0, -40,
		0, 1, 0, -40, 0, -40,
		0, 1, 0, 0, 70, 0
	};

	GLfloat bottom_face[] = {
		0, 1, 0.8, -40, 0, 40,
		0, 1, 0.8, 40, 0, 40,
		0, 1, 0.8, 0, -70, 0
	};

	GLfloat bottom_right[] = {
		0, 0, 1, 40, 0, 40,
		0, 0, 1, 40, 0, -40,
		0, 0, 1, 0, -70, 0
	};

	GLfloat bottom_left[] = {
		1, 0, 1, -40, 0, 40,
		1, 0, 1, -40, 0, -40,
		1, 0, 1, 0, -70, 0
	};

	GLfloat bottom_back[] = {
		1, 0, 0, 40, 0, -40,
		0, 1, 0, -40, 0, -40,
		0, 0, 1, 0, -70, 0
	};

	draw_oct_face(top_face);
	draw_oct_face(top_right);
	draw_oct_face(top_left);
	draw_oct_face(top_back);
	draw_oct_face(bottom_face);
	draw_oct_face(bottom_right);
	draw_oct_face(bottom_left);
	draw_oct_face(bottom_back);
}

void draw_oct_face(GLfloat * vertexes) {
	GLfloat normal[3] = { 0, 0, 0 };

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	for (int i = 0; i < 3; i++) {
		if (vertexes[4 + i * 6]) {
			normal[1] = vertexes[4 + i * 6];
		}
	}

	for (int i = 0; i < 2; i++) {
		if (vertexes[3 + i * 6] == vertexes[3 + (i + 1) * 6]) {
			normal[0] = vertexes[3 + i * 6];
		}
		if (vertexes[5 + i * 6] == vertexes[5 + (i + 1) * 6]) {
			normal[2] = vertexes[5 + i * 6];
		}
	}

	glInterleavedArrays(GL_C3F_V3F, 0, vertexes);
	GLubyte indeces[] = { 0, 1, 2 };

	glPushMatrix();
	glTranslatef(normal[0] * aspect, normal[1] * aspect, normal[2] * aspect);
	glNormal3fv(normal);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indeces);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void draw_sphere() {
	glPushMatrix();
	glTranslatef(0, 0, -300);
	glLineWidth(4);
	glColor3f(1, 0.7, 0);
	glutWireSphere(30, 8, 8);
	glPopMatrix();
	glLineWidth(1);
}

void light_init() {
	GLfloat position[] = { 0, 0, light_z, 1 };
	GLfloat diffuse[] = { 1, 1, 1};
	GLfloat spot_direction[] = { 0, 0, 1 };

	glEnable(GL_LIGHT0);
	//glPushMatrix();
	//glTranslatef(0, 0, -300);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glPopMatrix();
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 15.0);
}