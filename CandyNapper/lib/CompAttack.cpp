/*
 * CompAttack.cpp
 *
 *  Created on: 24/02/2012
 *      Author: kaseyo
 */

#include "CompAttack.h"
#include "Player.h"
#include "CandyNapper.h"
#include "InterfazGraphics.h"
#include "GEDynamic.h"
#include "HUD.h"
#include "Timer.h"
#include "InterfazMusic.h"

#include <sstream>
using namespace std;

namespace candy {

const float CompAttack::RangoGreta = 50.0;
const float CompAttack::FuerzaGreta = 20.0;
const float CompAttack::VelocidadGreta = 20.0;
const float CompAttack::CadenciaGreta = 100.0;

const float CompAttack::RangoHans = 10.0;
const float CompAttack::FuerzaHans = 30.0;
const float CompAttack::VelocidadHans = 10.0;
const float CompAttack::CadenciaHans = 150.0;

CompAttack::CompAttack(GEDynamic* entidad) {
	//Lo inicializamos a los valores de Hans
	_attackGreta = new Attack(entidad);
	_attackHans = new Attack(entidad);

	_attackHans->setCadencia(CadenciaHans);
	_attackHans->setFuerza(FuerzaHans);
	_attackHans->setRango(RangoHans);
	_attackHans->setVelocidad(VelocidadHans);
	_attackGreta->setCadencia(CadenciaGreta);
	_attackGreta->setFuerza(FuerzaGreta);
	_attackGreta->setRango(RangoGreta);
	_attackGreta->setVelocidad(VelocidadGreta);

	//cout << "HOLLLLAAAAA!!!!!!!!!!!!!!!!!!" << endl;
	//idSonido = InterfazMusic::getInstancia()->getMusicEngine()->LoadSound("Rain_wind.wav");
	//cout << "LLEGA??" << endl;
}

CompAttack::~CompAttack() {
	delete _attackGreta;
	delete _attackHans;
}

void
CompAttack::Update(GameEntity* entidad){
	Player* player = (Player*)entidad;

	/*
	Text* textoDebug2 = InterfazGraphics::getInstance()->getHUD()->getText2();
	ostringstream form_ataque;
	*/
	if(_attackGreta->getEntidad() == NULL){
		_attackGreta->setEntidad(CandyNapper::getInstancia()->getEm()->getPlayer());
	}
	if(_attackHans->getEntidad() == NULL){
		_attackHans->setEntidad(CandyNapper::getInstancia()->getEm()->getPlayer());
	}

	if(player->isAttacking())
	{
		bool ataco;
		int id_obj = InterfazGraphics::getInstance()->Seleccion();
		if(player->isHans()){
			ataco = _attackHans->Atacar(id_obj, GameEntity::Enemigo);
		}else if(player->isGreta()){
			ataco = _attackGreta->Atacar(id_obj, GameEntity::Enemigo);
		}
		if(ataco){
			//form_ataque << "Ataco a " << id_obj;
		/*	cout << "Reproduzco sonido " << idSonido << endl;
			InterfazMusic::getInstancia()->getMusicEngine()->setPosListener(player->getPosicion());
			InterfazMusic::getInstancia()->getMusicEngine()->S_Position(idSonido,player->getPosicion());
			InterfazMusic::getInstancia()->getMusicEngine()->S_Play(idSonido);*/
		}else{
			//form_ataque << "Intento atacar a " << id_obj << " pero fallo ";
		}
	}else{
		//form_ataque << "No estoy Atacando";
	}

	//textoDebug2->setTexto(form_ataque.str());
}

} /* namespace candy */
