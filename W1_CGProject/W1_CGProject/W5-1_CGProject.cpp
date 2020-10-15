#include <GL/glut.h>

GLsizei winWidth = 300, winHeight = 300;
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

void MyDisplay()
{
	glViewport(0, 0, 300, 300);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	
	glVertex3f(TopLeftX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
	glVertex3f(TopLeftX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
	glVertex3f(BottomRightX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
	glVertex3f(BottomRightX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
	glEnd();
	glFlush();
}

void MyMouceClick(GLint Button, GLint State, GLint X, GLint Y)
{
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		TopLeftX = (X - 150) * 2;
		TopLeftY = Y*2;	
	}	
}

void MyMouseMove(GLint X, GLint Y)
{
	BottomRightX = (X - 150) *2;
	BottomRightY = Y*2;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("W5-1_CGProject");

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouceClick);
	glutMotionFunc(MyMouseMove);
	glutMainLoop();
	
	return 0;
}