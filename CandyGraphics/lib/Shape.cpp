/*
 * Polygon.cpp
 *
 *  Created on: 08/02/2012
 *      Author: kaseyo
 */

#include "Shape.h"
#include "GestorRecursos.h"

namespace candy {

Shape::Shape(int numLados, Color color)
	: GNode(GNode::E_Polygon)
{
	c_numLados = numLados;
	c_color = color;
	id = -1;
	_idTextura = -1;
}

Shape::~Shape() {

}

Shape::Shape(const Shape &cop)
	:GNode(cop)
{
	copiarDesde(cop);
}

Shape&
Shape::operator=(const Shape& cop){
	if(this != &cop){
		copiarDesde(cop);
	}

	return *this;
}

void
Shape::copiarDesde(const Shape& cop){
	c_numLados = cop.c_numLados;
	c_color = cop.c_color;
}

void
Shape::setTexture(int id){
	_idTextura = id;
}

void
Shape::Render(bool seleccion){

	//glMatrixMode(GL_MODELVIEW);

	float segmentos=c_numLados;
	float incremento=2*M_PI/c_numLados;
	float angulo=-incremento/2; //Para que dibuje los poligonos horizontales y no salgan doblados

	if(id!=-1){
		glLoadName(id);
	}

	int t;
	GestorRecursos* g = GestorRecursos::getInstancia();

	if(_idTextura != -1){
		t = g->getTextura(_idTextura);
	}


	if(id != -1 || !seleccion){
		glColor4f(c_color.R(), c_color.G(), c_color.B(), c_color.A());

		if(t != -1){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,t);
		}

		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_TRIANGLE_FAN);
			for(int i=0; i<segmentos; i++){
				float x=10.0*cos(angulo);
				float y=10.0*sin(angulo);
				if(t != -1){
					glNormal3f(0.0,0.0,1.0);
					glTexCoord2d(cos(angulo)/2.0+0.5,sin(angulo)/2.0+0.5);
				}
				glVertex3f(x,y,0);
				angulo+=incremento;
			}
		glEnd();
		glDisable(GL_BLEND);

		if(t != -1){
			glDisable(GL_TEXTURE_2D);
		}
	}

#ifdef _DEBUG_
    cout << "Renderizo el poligono de " << c_numLados << " lados" << endl;
    cout << "Renderizo los hijos del poligono (" << hijos.size() << ")" << endl;
#endif
	RenderHijos(seleccion);
#ifdef _DEBUG_
	cout << "Vuelvo al poligono" << endl;
#endif
}

} /* namespace candy */
