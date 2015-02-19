/*
 * CandyGraphics.cpp
 *
 *  Created on: 17/11/2011
 *      Author: kaseyo
 */

#include "CandyGraphics.h"

using namespace candy;

CandyGraphics::CandyGraphics() {
	c_escena = new Scene();
}

CandyGraphics::~CandyGraphics() {
	delete c_escena;
}

CandyGraphics::CandyGraphics(const CandyGraphics& cop){
	copiarDesde(cop);
}

CandyGraphics&
CandyGraphics::operator=(const CandyGraphics& cop){
	if(this != &cop){
		this->~CandyGraphics();
		copiarDesde(cop);
	}

	return *this;
}
/*
int candy::CandyGraphics::seleccion(int x, int y)
{
	int seleccion=0;


	return seleccion;
}
*/

void
CandyGraphics::copiarDesde(const CandyGraphics& cop){
	c_escena = new Scene((Scene&)*cop.c_escena);
}

void
CandyGraphics::Render(){
	c_escena->Render(false);
}

Scene*
CandyGraphics::getScenePtr(){
	return c_escena;
}

void
CandyGraphics::InitOpenGL(){
	// Set color and depth clear value
    glClearColor(0.f, 0.f, 0.f, 0.f);
	glClearDepth(1.f);
	//glEnable(GL_CULL_FACE);
	// El resto de enables y parametros se encargan de hacerlos las camaras en cada Render
}

void
CandyGraphics::setClearColor(const Color& c){
	glClearColor(c.R(), c.G(), c.B(), c.A());
}


int candy::CandyGraphics::seleccion(int x, int y)
{
	int seleccion = -1;

	// formato de buffer, cada cuatro posiciones almacena:
	//      buffer[i]   = número de objetos
    //      buffer[i+1] = profundidad mínima
    //      buffer[i+2] = profuncidad máxima
    //      buffer[i+3] = nombre de la pila

    GLuint	buffer[1024];
    GLint	hits = 0;
    int     profundidad;


    GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(1024, buffer);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(-1);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	    glLoadIdentity();
		gluPickMatrix(x, y, 1.0f, 1.0f, viewport);
		c_escena->Render(true);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	hits= glRenderMode(GL_RENDER);

	//cout << "Nueva seleccion" << endl;
	if(hits>0){
		for (int i = 0; i < hits; i++)  // Recorre todos los objetos
		{
			//cout << "Num de objetos: " << buffer[i*4] << endl;
			//cout << "Trato ID: " << buffer[i*4+3] << endl;
			//cout << "Su z-minima: " << buffer[i*4+1] << endl;
			//cout << "Su z-maxima: " << buffer[i*4+2] << endl;

			if(i == 0){
				profundidad = buffer[i*4+1];
				seleccion=buffer[i*4+3];
			}

		// Si el objetos está más cerca que el seleccionado ahora
			if (buffer[i*4+1] < GLuint(profundidad))
			{
				seleccion = buffer[i*4+3];	    // Selecciona dicho objeto
				profundidad = buffer[i*4+1];	// Calcula su profundidad
			}
		}
	}



	return seleccion;
}
