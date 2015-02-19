/*
 * Line.cpp
 *
 *  Created on: 17/02/2012
 *      Author: kaseyo
 */

#include "Line.h"

namespace candy {

Line::Line(Vector3 puntoFinal, Color color, bool punteada)
	:GNode(GNode::E_Line), c_inicial(0, 0, 0)
{
	c_final = puntoFinal;
	c_color = color;
	c_punteada = punteada;
	_width = 1.0;
}

Line::Line(Vector3 puntoInicial, Vector3 puntoFinal, Color color, bool punteada)
	:GNode(GNode::E_Line)
{
	c_final = puntoFinal;
	c_inicial = puntoInicial;
	c_color = color;
	c_punteada = punteada;
	_width = 1.0;
}

Line::~Line(){

}

Line::Line(const Line& cop)
	:GNode(cop)
{
	copiarDesde(cop);
}

Line&
Line::operator=(const Line& cop){
	if(this != &cop){
		this->~Line();
		GNode::copiarDesde(cop);
		copiarDesde(cop);
	}

	return *this;
}

void
Line::copiarDesde(const Line& cop){
	c_final = cop.c_final;
	c_color = cop.c_color;
	c_punteada = cop.c_punteada;
}

void
Line::Render(bool seleccion){

	if(!seleccion){ //ÀTiene sentido renderizar una linea en modo seleccion?
		GLushort patron = 0x5555;
		int factor = 1;

		if(c_punteada){
			glLineStipple(factor,patron);
		}

		glLineWidth(_width);

		glColor4f(c_color.R(), c_color.G(), c_color.B(), c_color.A());

		glBegin(GL_LINES);
			glVertex3f(c_inicial.getX(), c_inicial.getY(), c_inicial.getZ());
			glVertex3f(c_final.getX(), c_final.getY(), c_final.getZ());
		glEnd();
	}

	RenderHijos(seleccion);
}

void
Line::setColor(Color color){
	c_color = color;
}

void
Line::setPuntoFinal(Vector3 puntoFinal){
	c_final = puntoFinal;
}

void
Line::setPunteada(bool punteada){
	c_punteada = punteada;
	if(punteada){
		glEnable(GL_LINE_STIPPLE);
	}else{
		glDisable(GL_LINE_STIPPLE);
	}
}

void
Line::setWidth(float ancho){
	_width = ancho;
}

} /* namespace candy */
