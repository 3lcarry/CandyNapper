/*
 * Plane.cpp
 *
 *  Created on: 09/03/2012
 *      Author: kaseyo
 */

#include "Plane.h"
#include "GestorRecursos.h"

namespace candy {

Plane::Plane()
	: GNode(GNode::E_Plane), _color(1.0, 1.0, 1.0, 1.0)
{
	_idTextura = -1;
}

Plane::~Plane() {

}

void
Plane::setColor(Color c){
	_color = c;
}

void
Plane::setTexture(int id){
	_idTextura = id;
}

void
Plane::Render(bool seleccion){
	if(id!=-1){
		glLoadName(id);
	}

	int t;
	GestorRecursos* g = GestorRecursos::getInstancia();

	if(_idTextura != -1){
		t = g->getTextura(_idTextura);
	}


	if(id != -1 || !seleccion){
		glColor4f(_color.R(), _color.G(), _color.B(), _color.A());

		if(t != -1){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,t);
		}

		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
			if(t != -1){
				glTexCoord2f(1, 1);
			}
			glVertex3f(  0.5f, -0.5f, 0);

			if(t != -1){
				glTexCoord2f(0, 1);
			}
			glVertex3f( -0.5f, -0.5f, 0);

			if(t != -1){
				glTexCoord2f(0, 0);
			}
			glVertex3f( -0.5f,  0.5f, 0);

			if(t != -1){
				glTexCoord2f(1, 0);
			}
			glVertex3f(  0.5f,  0.5f, 0);
		glEnd();
		glDisable(GL_BLEND);

		if(t != -1){
			glDisable(GL_TEXTURE_2D);
		}
	}

	RenderHijos(seleccion);
}

} /* namespace candy */
