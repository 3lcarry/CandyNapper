//Cabeceras de OpenGL segun el SO

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	//#include <GLUT/glut.h>
#elif _WIN32
	#include <Windows.h>
	#include <gl\GL.h>
	#include <gl\GLU.h>
	//#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	//#include <GL/glut.h>
#endif
