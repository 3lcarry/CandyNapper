#include <QtGui/QApplication>
#include "candyeditor.h"
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#elif _WIN32
	#include <Windows.h>
	#include <gl\GL.h>
	#include <gl\GLU.h>
	#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);
    CandyEditor w;
    w.show();

    return a.exec();
}
