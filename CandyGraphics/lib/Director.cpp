/*
 * DirectedCamera.cpp
 *
 *  Created on: 20/02/2012
 *      Author: kaseyo
 */

#include "Director.h"

namespace candy {

Director::Director(Vector3 ojo, Vector3 direccion, Vector3 up)
	: GNode(GNode::E_Director)
{
	c_ojo = ojo;
	c_direccion = direccion;
	c_up = up;

	_pila = MatrixStack::getInstance();
}

Director::~Director() {

}

void
Director::Render(bool seleccion){
	glMatrixMode(GL_PROJECTION);

	gluLookAt(c_ojo.getX(), c_ojo.getY(), c_ojo.getZ(), c_direccion.getX(), c_direccion.getY(), c_direccion.getZ(),
			c_up.getX(), c_up.getY(), c_up.getZ());

	glMatrixMode(GL_MODELVIEW);
	RenderHijos(seleccion);
}

void
Director::setReference(Vector3 direccion){
	c_direccion = direccion;
}

void
Director::setCenter(Vector3 ojo){
	c_ojo = ojo;
}

void
Director::setUp(Vector3 up){
	c_up = up;
}

} /* namespace candy */
