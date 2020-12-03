#define _CRT_SECURE_NO_WARNINGS

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

#define WIRE 0
#define SHADE 1

typedef struct {
	float x;
	float y;
	float z;
} Point;

typedef struct {
	unsigned int ip[3];
} Face;

int pnum;
int fnum;

Point* mpoint = NULL;
Face* mface = NULL;
GLfloat angle = 0;

int moving;
int mousebegin;
int light_moving;
float scalefactor = 1.0;
int scaling = 0;
int status = 0;
string fname = "c:\\OpenGL_model_data\\chair.dat";

void ReadModel()
{
	FILE* f1; char s[81]; int i;
	if (mpoint != NULL) delete mpoint;
	if (mface != NULL) delete mface;
	if ((f1 = fopen(fname.c_str(), "rt")) == NULL) { printf("No file\n"); exit(0); }

	fscanf(f1, "%s", s); printf("%s", s);
	fscanf(f1, "%s", s); printf("%s", s);
	fscanf(f1, "%d", &pnum); printf("%d\n", pnum);
	mpoint = new Point[pnum];
	for (i = 0; i < pnum; i++) {
		fscanf(f1, "%f", &mpoint[i].x);
		fscanf(f1, "%f", &mpoint[i].y);
		fscanf(f1, "%f", &mpoint[i].z);
		printf("%f %f %f\n", mpoint[i].x, mpoint[i].y, mpoint[i].z);
	}

	fscanf(f1, "%s", s); printf("%s", s);
	fscanf(f1, "%s", s); printf("%s", s);
	fscanf(f1, "%d", &fnum); printf("%d\n", fnum);
	mface = new Face[fnum];
	for (i = 0; i < fnum; i++) {
		fscanf(f1, "%d", &mface[i].ip[0]);
		fscanf(f1, "%d", &mface[i].ip[1]);
		fscanf(f1, "%d", &mface[i].ip[2]);
		printf("%d %d %d\n", mface[i].ip[0], mface[i].ip[1], mface[i].ip[2]);
	}

	fclose(f1);
}

void DrawWire(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(1);
	glutSwapBuffers();
}

void DrawShade(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(1);
	glutSwapBuffers();
}

void MakeGL_Model(void)
{
	int i;
	glShadeModel(GL_SMOOTH);
	if (glIsList(1)) glDeleteLists(1, 1);
	glNewList(1, GL_COMPILE);
	glPushMatrix();
	glRotatef(angle, 0.0, 1.0, 0.0);
	glScalef(scalefactor, scalefactor, scalefactor);
	glColor3f(0.0, 0.6, 0.9);
	for (i = 0; i < fnum; i++) {
		glBegin(GL_TRIANGLES);
		glVertex3f(mpoint[mface[i].ip[0]].x,
			mpoint[mface[i].ip[0]].y, mpoint[mface[i].ip[0]].z);
		glVertex3f(mpoint[mface[i].ip[1]].x,
			mpoint[mface[i].ip[1]].y, mpoint[mface[i].ip[1]].z);
		glVertex3f(mpoint[mface[i].ip[2]].x,
			mpoint[mface[i].ip[2]].y, mpoint[mface[i].ip[2]].z);
		glEnd();
	}
	glPopMatrix();
	glEndList();
}

void GLSetupRC(void)
{
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, 1.0, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(400.0, 400.0, 400.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.); 
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
	MakeGL_Model();
	if (status == WIRE)
		DrawWire();
	else
		DrawShade();
}

void keyboard(unsigned char key, int x, int y)
{
	printf("key %d\n", key);
	switch (key)
	{
	case 'w':
		status = WIRE; glutPostRedisplay(); break;
	case 's':
		status = SHADE; glutPostRedisplay(); break;
	case '1':
		fname = "c:\\OpenGL_model_data\\cube.dat";
		ReadModel(); glutPostRedisplay(); break;
	case '2':
		fname = "c:\\OpenGL_model_data\\mysphere.dat";
		ReadModel(); glutPostRedisplay(); break;
	case '3':
		fname = "c:\\OpenGL_model_data\\mysuperellipsoid.dat";
		ReadModel(); glutPostRedisplay(); break;
	case '4':
		fname = "c:\\OpenGL_model_data\\mytorus.dat";
		ReadModel(); glutPostRedisplay(); break;
	case '5':
		fname = "c:\\OpenGL_model_data\\mybspline.dat";
		ReadModel(); glutPostRedisplay(); break;
	case '6':
		fname = "c:\\OpenGL_model_data\\teapot.dat";
		ReadModel(); glutPostRedisplay(); break;
	case '7':
		fname = "c:\\OpenGL_model_data\\mycylinder.dat";
		ReadModel(); glutPostRedisplay(); break;
	}
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		moving = 1;
		mousebegin = x;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		scaling = 1;
		mousebegin = x;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		scaling = 0;
	}
}

void motion(int x, int y) {
	if (scaling) {
		scalefactor = scalefactor * (1.0 + (mousebegin - x) * 0.0001);
		glutPostRedisplay();
	}
	if (moving) {
		angle = angle + (x - mousebegin); mousebegin = x;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Simple modeling");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	ReadModel();
	GLSetupRC();
	glutMainLoop();
	return 0;
}