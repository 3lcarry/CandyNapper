/*
 * HUD.cpp
 *
 *  Created on: 01/03/2012
 *      Author: kaseyo
 */

#include "HUD.h"

#include "InterfazGraphics.h"

namespace candy {

HUD::HUD(Scene* escena, Ventana* ventana) {

	float ancho = ventana->getWidth();
	float alto = ventana->getHeight();
	_cam2D = escena->addCamera2D(0, ancho, 0, alto);
	_cam2D->setLight(false);

	//Anyadimos el minimapa al HUD (se queda con unas dimensiones aprox: 280x210)
	_minimapa = _cam2D->addTransformation();
	Transformation* t_caja = _minimapa->addTransformation();
	t_caja->addShape(4, Color(0.3, 0.3, 0.3, 0.8));
	t_caja->Scale(20, 15, 1);
	_minimapa->Translate(ancho - 150, alto - 120);

	//Anyadimos la mirilla al HUD
	_mirilla = _cam2D->addTransformation();
	_mirilla->Translate(ancho / 2, alto / 2);
	float separacion_ejes = 2.5;
	Color color_ejes(1.0, 1.0, 1.0, 1.0);
	//Eje hacia arriba
	Transformation* t_up = _mirilla->addTransformation();
	t_up->Translate(0, separacion_ejes);
	Line* l_up = t_up->addLine(Vector3(0, 10, 0), color_ejes, true);
	//Eje hacia abajo
	Transformation* t_down = _mirilla->addTransformation();
	t_down->Translate(0, -separacion_ejes);
	Line* l_down = t_down->addLine(Vector3(0, -10, 0), color_ejes, true);
	//Eje hacia derecha
	Transformation* t_right = _mirilla->addTransformation();
	t_right->Translate(separacion_ejes, 0);
	Line* l_right = t_right->addLine(Vector3(10, 0, 0), color_ejes, true);
	//Eje hacia izquierda
	Transformation* t_left = _mirilla->addTransformation();
	t_left->Translate(-separacion_ejes, 0);
	Line* l_left = t_left->addLine(Vector3(-10, 0, 0), color_ejes, true);

	Transformation* t_cent = _cam2D->addTransformation();
	t_cent->setTranslation(Vector2(ancho / 2 - 250, alto - 100));
	_mensajeCentral = t_cent->addText();
	_mensajeCentral->setTexto("A Tope 00 Segundos");
	_mensajeCentral->setTamanyo(40);
	_mensajeCentral->setColor(Color::Red);
	_mensajeCentral->setActive(false);


	//DEBUG
	//Anyadimos el texto de debugging 1
	Transformation* t_tex1 = _cam2D->addTransformation();
	t_tex1->Translate(50, alto - 50, 0);
	_text1 = t_tex1->addText();
	_text1->setColor(Color(1.0, 0.0, 0.0, 1.0));
	_text1->setTamanyo(15);
	_text1->setTexto("CandyNapper v0.9");

	//Anyadimos el texto de debugging 2

	Transformation* t_tex2 = _cam2D->addTransformation();
	t_tex2->Translate(50, alto - 100, 0);
	_text2 = t_tex2->addText();
	_text2->setColor(Color(1.0, 0.0, 0.0, 1.0));
	_text2->setTamanyo(15);
	_text2->setTexto("");

	//Anyadimos la caja de la consola
	Transformation* t_cons = _cam2D->addTransformation();
	ventana->getConsolePtr()->setGNode(t_cons);

	//Anyadimos al HUD el cuadro de debug
	_box1 = _cam2D->addTransformation();
	Transformation* t_box1 = _box1->addTransformation();
	t_box1->Scale(10, 10);
	_box1->Translate(100, 100);
	t_box1->addShape(4, Color(1.0, 1.0, 1.0, 0.8));
}

HUD::~HUD() {

}

void HUD::Resize(float ancho, float alto) {
	_cam2D->setParameters2D(0, ancho, 0, alto);

	_mirilla->setTranslation(ancho / 2.0, alto / 2.0);
	_minimapa->setTranslation(ancho - 150, alto - 120);
}

Text*
HUD::getText1() {
	return _text1;
}

Text*
HUD::getText2() {
	return _text2;
}

Transformation*
HUD::getMinimap() {
	return _minimapa;
}

Camera *HUD::getHUDCamera() {
	return _cam2D;
}

Transformation*
HUD::getBox1() {
	return _box1;
}

Text *HUD::getMensajeCentral() {
	return _mensajeCentral;
}

} /* namespace candy */
