// W1_CGProject.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <GL/glut.h>

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
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