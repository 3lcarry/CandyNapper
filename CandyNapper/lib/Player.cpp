/*
 * Player.cpp
 *
 *  Created on: 24/02/2012
 *      Author: kaseyo
 */

#include "Player.h"
#include "IComponent.h"

#include "CompGraphicPlayer.h"
#include "CompMouse.h"
#include "CompKeyboard.h"
#include "CompAttack.h"
#include "CompPhysics.h"
#include "CompMinimap.h"
#include "CompHealth.h"
#include "CompPlayer.h"
#include "CompMusic.h"

namespace candy {

Player::Player(Vector3 posicion) :
		GEDynamic(GameEntity::Player, 0, posicion) {

	_modoAtope = false;

	//Init de atributos basicos
	_personaje = Hans;
	_apuntando = false;
	_radio = 1.0;
	_vidaRestante = 100;
	_vidaTotal = _vidaRestante;
	_muerto = false;
	//En un futuro cercano habra que tener esto en cuenta
	//para las vidas de cada uno
	/*
	 switch(Personaje){
	 case Hans:
	 _vidaTotal =
	 break;

	 case Greta:

	 break;
	 }
	 */

	_convexHull = PolygonFactory::Circulo(
			Vector2(posicion.getX(), -posicion.getZ()), _radio);

	//Init de los componente
	//Anyado el componente de mouse (lo metemos al principio)
	IComponent* mc = new CompMouse();
	c_componentes.push_back(mc);

	//Anyado el componente de keyboard (lo metemos al principio)
	IComponent* kc = new CompKeyboard();
	c_componentes.push_back(kc);

	//Lo pongo el primero, para meter por delante al mouse y al keyboard
	IComponent* ac = new CompAttack(this);
	c_componentes.push_back(ac);

	//Anyado el componente de fisica
	IComponent* fc = new CompPhysics(this);
	c_componentes.push_back(fc);

	//Anyadimos el componente de minimapa
	IComponent* minimapc = new CompMinimap(this);
	c_componentes.push_back(minimapc);

	IComponent* healthc = new CompHealth(this);
	c_componentes.push_back(healthc);

	//Anyado el componente grafico especifico del player
	IComponent* gc = new CompGraphicPlayer(this);
	c_componentes.push_back(gc);

	IComponent* pc = new CompPlayer();
	c_componentes.push_back(pc);

	IComponent* cm = new CompMusic(this);
	c_componentes.push_back(cm);

}

Player::~Player() {

}

void Player::setPersonaje(Personaje pj) {
	_personaje = pj;
}

bool Player::isGreta() {
	return _personaje == Greta;
}

bool Player::isHans() {
	return _personaje == Hans;
}

void Player::setApuntando(bool apuntando) {
	_apuntando = apuntando;
}

bool Player::isApuntando() {
	return _apuntando;
}

bool Player::isAttacking() {
	return _atacando;
}

void Player::setAttacking(bool atacando) {
	_atacando = atacando;
}

void Player::switchPersonaje() {
	if (_personaje == Greta) {
		_personaje = Hans;
	} else {
		_personaje = Greta;
	}
}

void Player::setModoATope(bool modo) {
	_modoAtope = modo;
}

bool Player::getModoATope() {
	return _modoAtope;
}

} /* namespace candy */
