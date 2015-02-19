/*
 * World3D.cpp
 *
 *  Created on: 01/03/2012
 *      Author: kaseyo
 */

#include "World3D.h"
#include "InterfazGraphics.h"

namespace candy {

World3D::World3D(Scene* escena, Ventana* v) {
	float ancho_v = v->getWidth();
	float alto_v = v->getHeight();

	//A�adimos y nos guardamos los punteros a las dos camaras
	_cam3D = escena->addCamera(0.01, 500.0, ancho_v/alto_v , 20);
	//_sky = _cam3D->addTransformation();

	//A�adimos las luces
	_cam3D->addLight(Vector3(-2.5, 3, 1), Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(0.3, 0.3, 0.3), 0);
	_cam3D->addLight(Vector3(2.0, 3, 1), Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(0.3, 0.3, 0.3), 1);
	_cam3D->addLight(Vector3(0, 5, -1), Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(0.3, 0.3, 0.3), 2);
	_cam3D->addLight(Vector3(0, 3, -20), Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(0.3, 0.3, 0.3), 3);

	//_sky = _cam3D->addTransformation();
	//trans_esc->setScalation(1, 1, 1);

	//Inicializamos la transformacion de la escena y la de la camara (encargados de mover la escena)
	Vector3 center(0, 0, 0);
	Vector3 reference(0, 0, -1);
	Vector3 up(0, 1, 0);
	_director = _cam3D->addDirector(center, reference, up);

	_escena = _director->addTransformation();
	_escena->setOrder(true);

	//DEBUG-------------
		//Pintamos el skybox
	_sky = _cam3D->addTransformation();
	_sky->setLight(false);
	_sky->setOrder(true);
	_sky->setDepth(false);
	_sky->Scale(600, 100, 600);

	Box* bBox = _sky->addBox(InterfazGraphics::T_SkyFront, InterfazGraphics::T_SkyBack,
							InterfazGraphics::T_SkyTop, InterfazGraphics::T_SkyBottom,
							InterfazGraphics::T_SkyLeft, InterfazGraphics::T_SkyRight);

		//Anyadimos el suelo (un rectangulo "verde")
	Transformation* t_suelo = _escena->addTransformation();
	t_suelo->setLight(false);
	Plane* p_suelo = t_suelo->addPlane();
	p_suelo->setTexture(InterfazGraphics::T_Suelo);
	t_suelo->Rotate(0, CandyMath::grad2rad(90));
	t_suelo->Scale(1000, 1, 1000);
	t_suelo->Translate(0, 0, 0);
}

World3D::~World3D() {

}

void
World3D::Resize(float ancho, float alto){
	_cam3D->setParameters3D(0.01, 500.0, ancho/alto , 20);
}

Camera*
World3D::getCamera3D(){
	return _cam3D;
}

Transformation*
World3D::getScene3D(){
	return _escena;
}

Director*
World3D::getDirector(){
	return _director;
}

Transformation*
World3D::getSky(){
	return _sky;
}

} /* namespace candy */
