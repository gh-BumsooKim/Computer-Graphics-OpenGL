#include <iostream>
#include <GL/glut.h>

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	//glEnable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glVertex2f(-0.3, -0.45);
	glVertex2f(0.3, -0.45);
	glVertex2f(0.5, 0.1);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.5, 0.1);
	glEnd();
	glFlush();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("BumsooKim");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}