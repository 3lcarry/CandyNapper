/*
 * MouseComponent.cpp
 *
 *  Created on: 16/02/2012
 *      Author: kaseyo
 */

#include "CompMouse.h"
#include "Player.h"


namespace candy {

CompMouse::CompMouse() {
	//El mouse debemos inicializarlo a partir de una ventana
	c_ventana = InterfazGraphics::getInstance()->getVentana();
	/*c_mouse = new Raton(c_ventana);*/
	c_centro = Vector2(c_ventana->getWidth()/2, c_ventana->getHeight()/2);
	Raton::setPosition(c_centro, c_ventana);
}

CompMouse::~CompMouse() {
	/*delete c_mouse;*/
}

void
CompMouse::Update(GameEntity* entidad){
	if(c_ventana->isFocused()){
		float ancho = c_ventana->getWidth();
		float alto = c_ventana->getHeight();

		Player* player = (Player*)entidad;

		Vector2 pos_raton =Raton::getPosition(c_ventana);

		Raton::setPosition(c_centro, c_ventana);

		c_ventana->ShowMouse(false);

		float dx = c_centro.getX() - pos_raton.getX();

		dx /= 10;

		if(dx != 0){
			float tope = 2.0 * M_PI;
			float coef_x = tope / ancho;

			float drad_x = dx * coef_x;

			float nuevo_angulo = player->getVisionX() + drad_x;

			if(nuevo_angulo > tope){
				nuevo_angulo = 0;
			}else if(nuevo_angulo < -tope){
				nuevo_angulo = 0;
			}

			player->setVisionX(nuevo_angulo);
		}

		float dy = c_centro.getY() - pos_raton.getY();
		dy /= 1;

		if(dy != 0){
			float tope = CandyMath::grad2rad(10);
			float coef_y =  tope / alto;

			float drad_y = dy * coef_y;

			float nuevo_angulo = player->getVisionY() - drad_y;

			if(nuevo_angulo > tope ){
				nuevo_angulo = tope;
			}else if(nuevo_angulo < -tope){
				nuevo_angulo = -tope;
			}

			player->setVisionY(nuevo_angulo);
		}

		if(Raton::isPressed(Raton::Izquierdo)){
			player->setAttacking(true);
		}else{
			player->setAttacking(false);
		}
	}
}

} /* namespace candy */
