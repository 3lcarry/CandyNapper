/*
 * Camera.cpp
 *
 *  Created on: 19/11/2011
 *      Author: kaseyo
 */

#include "Camera.h"
using namespace candy;

/*
 * 2D------------
 * param1 -> left
 * param2 -> right
 * param3 -> top
 * param3 -> bottom
 * 3D------------
 * param1 -> near
 * param2 -> far
 * param3 -> aspectRatio
 * param4 -> fov
 */

Camera::Camera(float param1, float param2, float param3, float param4, bool tresde) : GNode(GNode::E_Camera)
{
	if(tresde){
		setParameters3D(param1, param2, param3, param4);
	}else{
		setParameters2D(param1, param2, param3, param4);
	}
}

Camera::~Camera(){

}

Camera::Camera(const Camera & cop) : GNode(cop)
{
	copiarDesde(cop);
}

Camera &
Camera::operator =(const Camera & cop){
	if(&cop != this){
		this->~Camera();
		GNode::copiarDesde(cop);
		copiarDesde(cop);
	}

	return *this;
}

void
Camera::copiarDesde(const Camera & cop){
	c_aspectRatio = cop.c_aspectRatio;
	c_far = cop.c_far;
	c_near = cop.c_near;
	c_fov = cop.c_fov;
}

void
Camera::setParameters3D(float near, float far, float aspectRatio, float fov){
	c_near = near;
	c_far = far;
	c_aspectRatio = aspectRatio;
	c_fov = fov;

	c_3D = true;
}

void
Camera::setParameters2D(float left, float right, float top, float bottom){
	c_left = left;
	c_right = right;
	c_top = top;
	c_bottom = bottom;

	c_3D = false;
}

void
Camera::Render(bool seleccion){

	//Setteamos la projection
	glMatrixMode(GL_PROJECTION);

	if(c_3D){
		//glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		//glEnable(GL_LIGHTING);
		//Ponemos la perspectiva
		gluPerspective(c_fov, c_aspectRatio, c_near, c_far);
	}else{
		//glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);
		//glDisable(GL_LIGHTING);
		//Ponemos la paralela
		gluOrtho2D(c_left, c_right, c_top, c_bottom);
	}

	//Ponemos la Modelview otra vez para seguir renderizando
	glMatrixMode(GL_MODELVIEW);

#ifdef _DEBUG_
	cout << "Renderizo la camara" << endl;
	cout << "Renderizo los hijos de la camara (" << hijos.size() << ")" << endl;
	cout << endl;
#endif
	RenderHijos(seleccion);
#ifdef _DEBUG_
	cout << endl;
	cout << "Vuelvo a la camara" << endl;
#endif
}

int Camera::seleccion(int x, int y)
{
	int seleccion = 0;

	// formato de buffer, cada cuatro posiciones almacena:
	//      buffer[i]   = número de objetos
    //      buffer[i+1] = profundidad mínima
    //      buffer[i+2] = profuncidad máxima
    //      buffer[i+3] = nombre de la pila

    GLuint	buffer[1024];
    GLint	hits = 0;
    int     profundidad;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

		Render(true);
		//c_escena->Render(true);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	hits= glRenderMode(GL_RENDER);

	if(hits>0){
		for (int i = 0; i < hits; i++)  // Recorre todos los objetos
		{
			//cout << "Num de objetos: " << buffer[i*4] << endl;
			//cout << "Trato ID: " << buffer[i*4+3] << endl;
			//cout << "Su z-minima: " << buffer[i*4+1] << endl;
			//cout << "Su z-maxima: " << buffer[i*4+2] << endl;+

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




