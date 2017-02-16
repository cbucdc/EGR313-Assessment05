#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>
/*
Richard Christensen
Christopher Chen
John Syfacunda
Taylor Moe
*/


GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 1;
double pi = atan(1) * 4;
double theta1 = 0;
double earthOrbitRadius = 4;
double moonOrbitRadius = 1;
double systemDepth = -20;
double X=0, Y=0, Z = -20;
int earthStepSize = 60;
int refreshMills = 1000/60;        // refresh interval in milliseconds [NEW]
long long count = 0;

void display(void);
void reshape(int x, int y);

// Called back when timer expired [NEW]
void timer(int value) {
	glutPostRedisplay();      // Post re-paint request to activate display()
	glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(350, 350);
	glutCreateWindow("Sphere");
	zRotated = 30.0;
	xRotated = 43;
	yRotated = 50;

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}


void display(void)
{
	theta1 = 2*pi*(count % earthStepSize) / earthStepSize;
	glMatrixMode(GL_MODELVIEW);  //https://www.opengl.org/discussion_boards/showthread.php/133880-Diference-between-GL_MODELVIEW-and-GL_PROJECTION

								 // clear the drawing buffer.
	glClear(GL_COLOR_BUFFER_BIT);

	gluLookAt(1, 1, 1, X, Y, Z, 0, 0, 0);
	//earth
	glLoadIdentity();
	double ex = X + earthOrbitRadius*cos(theta1);
	double ey = Y + earthOrbitRadius*sin(theta1) / 2;
	glTranslatef(ex,ey, Z);
	glColor3f(0, 0, 1);
	glutWireSphere(radius / 2, 50, 50);

	glLoadIdentity();
	glTranslatef(ex, ey + moonOrbitRadius*cos(theta1 * 3), Z + moonOrbitRadius*sin(theta1 *3));
	glColor3f(0.8, 0.8, 0.8);
	glutSolidSphere(radius / 4, 25, 25);

	// clear the identity matrix.
	glLoadIdentity();
	// traslate the draw by z = -4.0
	// Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
	glTranslatef(X, Y, Z);
	// Red color used to draw.
	glColor3f(1, 0.7, 0.0);
	// changing in transformation matrix.
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);
	// built-in (glut library) function , draw you a sphere.
	glutSolidSphere(radius, 50, 50);
	//glutSolidSphere(radius, 5, 5);
	// Flush buffers to screen

	glFlush();
	// sawp buffers called because we are using double buffering 
	// glutSwapBuffers();
	count++;
}

void reshape(int x, int y)
{
	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.0, 100);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);  //Use the whole window for rendering
} //-See more at : http ://www.codemiles.com/c-opengl-examples/draw-a-solid-sphere-using-opengl-t9008.html#sthash.N7WK8I5F.dpuf
