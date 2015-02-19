/*
 * Menu.cpp
 *
 *  Created on: 06/03/2012
 *      Author: carrillo
 */

#include "Menu.h"

namespace candy {

Menu::Menu(Scene *escena, Ventana *v, string titulo,int tam) {
	float ancho = v->getWidth();
	float alto = v->getHeight();
	_ancho = ancho;
	_alto = alto;

	_Cam2D = escena->addCamera2D(0, ancho, 0, alto);
	_Cam2D->setLight(false);
	_Cam2D->setDepth(false);

	Transformation* tpanel = _Cam2D->addTransformation();
	tpanel->setTranslation(_ancho/2.0,_alto/2.0,-1);
	tpanel->Scale(_ancho,_alto,1);
	_fondo = tpanel->addPlane();
	_fondo->setActive(false);

	Transformation* t_title = _Cam2D->addTransformation();
	Text* title = t_title->addText();
	title->setTamanyo(tam);
	title->setTexto(titulo);
	title->setColor(Color(1.0, 0.0, 0.0, 1.0));
	t_title->Translate(ancho/2.0- title->getWidth()/2.0  , alto * 3.0 / 4.0);
}

void
Menu::setFondo(int textura){
	_fondo->setTexture(textura);
	_fondo->setActive(true);
}

void
Menu::setFondo(Color color)
{
	_fondo->setColor(color);
	_fondo->setActive(true);
}

Menu::~Menu() {
	_botones.clear();
}

Camera *Menu::getMenuCamera() {
	return _Cam2D;
}

void Menu::addButton(Vector2 pos, string texto, int id, int width, int heigth) {
	Buttons* boton = new Buttons();
	Transformation* transformacion = _Cam2D->addTransformation();
	transformacion->setTranslation(pos);
	boton->_Boton = transformacion->addButton(width, heigth, texto);
	boton->_Position = transformacion;
	boton->_Boton->setID(id);
	_botones.push_back(boton);
}

bool Menu::deleteButton(int id) {
	bool borrado = false;

	list<Buttons*>::iterator it;
	for(it = _botones.begin(); it != _botones.end() && !borrado;it++)
	{
		if((*it)->_Boton->getID() == id)
		{
			(*it)->_Position->setDestroy(true);
			delete (*it);
			borrado = true;
			it = _botones.erase(it);
		}
	}

	return borrado;
}

} /* namespace candy */
