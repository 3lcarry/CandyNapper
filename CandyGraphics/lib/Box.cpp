/*
 * Box.cpp
 *
 *  Created on: 29/02/2012
 *      Author: kaseyo
 */

#include "Box.h"
#include "OpenGL.h"
#include "GestorRecursos.h"
#include "Transformation.h"

namespace candy {

Box::Box()
	:GNode(GNode::E_Box)
{
	init();
}

Box::Box(int idFront, int idBack, int idTop, int idBottom, int idLeft, int idRight)
	:GNode(GNode::E_Box)
{
	init();

	_planos[Front]->setTexture(idFront);
	_planos[Back]->setTexture(idBack);
	_planos[Top]->setTexture(idTop);
	_planos[Bottom]->setTexture(idBottom);
	_planos[Left]->setTexture(idLeft);
	_planos[Right]->setTexture(idRight);
}

void
Box::init(){
	for(int i = 0; i < 6; i++){
		Transformation* t = this->addTransformation();
		switch(i){
		case Front:
			t->Translate(0, 0, -0.5);
			break;
		case Back:
			t->Scale(-1, 1, 1);
			t->Translate(0, 0, 0.5);
			break;
		case Left:
			t->Scale(1, 1, -1);
			t->Rotate(1, CandyMath::grad2rad(-90));
			t->Translate(-0.5, 0, 0);
			break;
		case Right:
			t->Scale(1, 1, -1);
			t->Rotate(1, CandyMath::grad2rad(90));
			t->Translate(0.5, 0, 0);
			break;
		case Top:
			//t->Scale(1, -1, 1);
			t->Rotate(0, CandyMath::grad2rad(90));
			t->Translate(0, 0.5, 0);
			break;
		case Bottom:
			//t->Scale(1, -1, 1);
			t->Rotate(0, CandyMath::grad2rad(-90));
			t->Translate(0, -0.5, 0);
			break;
		}
		_planos[i] = t->addPlane();
	}
}

Box::~Box() {

}

void
Box::Render(bool seleccion){
	RenderHijos(seleccion);
}

} /* namespace candy */
