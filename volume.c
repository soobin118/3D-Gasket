/* Recursive subdivision of triangle to form Sierpinski gasket */

#include <GL/glut.h>
#include <stdlib.h>

typedef float point2[3];

/* initial triangle */

point2 v[] = { { -1.0, -0.58, 0.0 },{ 1.0, -0.58, 0.0 },{ 0.0, 1.15, 0.0 },{ 0.0, 0.0, 1.63 } };

int n;

void triangle(point2 a, point2 b, point2 c, point2 d)

/* display one triangle  */
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(a);
	glVertex3fv(d);
	glVertex3fv(c);
	glColor3f(0.0, 0.6, 0.0);
	glVertex3fv(a);
	glVertex3fv(d);
	glVertex3fv(b);
	glColor3f(0.0, 0.0,0.6 );
	glVertex3fv(c);
	glVertex3fv(d);
	glVertex3fv(b);
	glEnd();
}

void divide_triangle(point2 a, point2 b, point2 c, point2 d,int m)
{

	/* triangle subdivision using vertex numbers */

	point2 v0, v1, v2, v3, v4, v5;
	int j;
	if (m>0)
	{
		for (j = 0; j < 3; j++) v0[j] = (a[j] + b[j]) / 2;
		for (j = 0; j < 3; j++) v1[j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) v2[j] = (b[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) v3[j] = (a[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) v4[j] = (b[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) v5[j] = (c[j] + d[j]) / 2;
		divide_triangle(a, v0, v1,v3, m - 1);
		divide_triangle( v1, v2,c,v5, m - 1);
		divide_triangle(b,v2,v0,  v4, m - 1);
		divide_triangle(v3, v4,v5,d,   m - 1);
	}
	else(triangle(a, b, c, d)); /* draw triangle at end of recursion */
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	divide_triangle(v[0], v[1], v[2],v[3], n);
	glFlush();
}

void myinit()
{
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
}

void main(int argc, char **argv)
{
	n = atoi(argv[1]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D Gasket");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}