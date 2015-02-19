/*
 * Text.cpp
 *
 *  Created on: 12/02/2012
 *      Author: carrillo
 */

#include "Text.h"

namespace candy {

Text::Text() :
		GNode(GNode::E_Text) {
	fuente = new FTGLPixmapFont(
			GestorRecursos::getInstancia()->getFontPaht(
					GestorRecursos::E_Anarchy).c_str());
	tamanyo = 10;
	if (fuente != NULL)
		fuente->FaceSize(tamanyo);
	texto = "";
	animationActivated = false;
}

Text::Text(const Text & o) :
		GNode(o) {
	copiarDesde(o);
}

Text::~Text() {
	if (fuente != NULL) {
		delete fuente;
	}
	fuente = NULL;
	tamanyo = 10;
}

void Text::Render(bool seleccion) {
	if (fuente != NULL && !seleccion) { //ÀTiene sentido renderizar texto en seleccion?
		if (id != -1) {
			glLoadName(id);
		}

		if (animationActivated) {
			long int tIncrementado = Timer::getTimeElapsed()
					- animationLastTime;

			int recorrido = animationMax - animationMin;
			int incremento = tIncrementado * recorrido / animationDuracion;

			if (dir < 0) {
				incremento = recorrido - incremento;
			}

			if(transformacion != NULL)
				transformacion->setTranslation(Vector2(-2*incremento,0));

			setTamanyo(animationMin + incremento);

			if ((dir == 1 && tamanyo >= animationMax)
					|| (dir == -1 && tamanyo <= animationMin)) {
				dir *= -1;
				animationLastTime = Timer::getTimeElapsed();
			}

		}

		glColor4f(color.R(), color.G(), color.B(), color.A());
		glRasterPos2d(0, 0);
		fuente->Render(texto.c_str());
	}

	RenderHijos(seleccion);
}

void Text::setTamanyo(int tam) {
	tamanyo = tam;
	if (fuente != NULL)
		fuente->FaceSize(tamanyo);
}

bool Text::setFont(int idFuente) {
	bool resultado = false;
	this->fuente = new FTGLPixmapFont(
			GestorRecursos::getInstancia()->getFontPaht(idFuente).c_str());
	if (fuente != NULL) {
		resultado = true;
		fuente->FaceSize(tamanyo);
	}

	return resultado;
}
bool Text::setFont(FTGLPixmapFont *fuente) {
	if (this->fuente != NULL)
		delete fuente;
	this->fuente = fuente;
	if (this->fuente != NULL)
		this->fuente->FaceSize(tamanyo);
	return true;
}

int Text::getTamanyo() {
	return tamanyo;
}

string Text::getTexto() {
	return texto;
}

void Text::setTexto(string t) {
	texto = t;
}

float Text::getWidth() {
	float width = 0;

	width = (tamanyo / 2.0) * texto.length();

	return width;
}

void Text::setFontAnimated(int min, int max, int milisegundos) {
	animationActivated = true;
	animationMin = min;
	animationMax = max;
	animationLastTime = Timer::getTimeElapsed();
	animationDuracion = milisegundos;
	dir = 1;
	setTamanyo(min);
}

void Text::desactiveAnimated() {
	animationActivated = false;
}

void Text::setTransformation(Transformation *trans) {
	transformacion = trans;
}

void Text::copiarDesde(const Text & o) {
	fuente = new FTGLPixmapFont(*(o.fuente));
	tamanyo = o.tamanyo;
	texto = o.texto;
	fuente->FaceSize(tamanyo);
}

void Text::setColor(const Color& color) {
	this->color = color;
}

} /* namespace candy */
