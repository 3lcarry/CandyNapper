/*
 * KeyComponent.cpp
 *
 *  Created on: 19/01/2012
 *      Author: kaseyo
 */

#include "CompKeyboard.h"
#include "GEDynamic.h"
#include "CandyMath.h"
#include "Player.h"
#include "Timer.h"

#include "CandyNapper.h"	//TODO: Quitar cuando no movamos enemigos

namespace candy {

CompKeyboard::CompKeyboard() {
	c_mapAccion[Teclado::W] = Adelante;
	c_mapAccion[Teclado::A] = Izquierda;
	c_mapAccion[Teclado::S] = Atras;
	c_mapAccion[Teclado::D] = Derecha;
	c_mapAccion[Teclado::LShift] = Apuntando;
	c_mapAccion[Teclado::C] = CambioPersonajes;

	//Init del estado de las acciones a false
	map<Accion, bool>::iterator it;
	for(it = c_mapEstado.begin(); it != c_mapEstado.end(); it++){
		it->second = false;
	}

	_cambioPj = Timer::getTimeElapsed();
}

CompKeyboard::~CompKeyboard() {

}

CompKeyboard::CompKeyboard(const CompKeyboard & kc){
	copiarDesde(kc);
}

CompKeyboard &
CompKeyboard::operator =(const CompKeyboard & kc){
	if(this != &kc){
		copiarDesde(kc);
	}

	return *this;
}

void
CompKeyboard::Update(GameEntity *entidad){
	Player* player = (Player*) entidad;

	/* Parametros que se asignaran finalmente al player */
	float angulo = 0.0, velocidad = GEDynamic::VelocidadNormal;
	bool modificado = true;

	/* Actualizo el estado de las teclas */
	map<Teclado::Tecla, Accion>::iterator it_accion;

	for(it_accion = c_mapAccion.begin(); it_accion != c_mapAccion.end(); it_accion++){
		if(c_teclado.isPulsada(it_accion->first)){
			c_mapEstado[it_accion->second] = true;
		}else{
			c_mapEstado[it_accion->second] = false;
		}
	}

	/* Actualizo la logica del player */
	bool izquierda = c_mapEstado[Izquierda];
	bool derecha = c_mapEstado[Derecha];
	bool delante = c_mapEstado[Adelante];
	bool detras = c_mapEstado[Atras];

	if(!izquierda && derecha){ //Hacia E
		if(delante && !detras){
			angulo = -M_PI/4.0; //NE
		}else if(!delante && detras){
			angulo = -M_PI/4.0 - M_PI/2.0; //SE
		}else if(!delante && !detras){
			angulo = -M_PI/2.0; //E
		}else{
			velocidad = 0.0; //NaN
			modificado = false;
		}
	}else if(izquierda && !derecha){ //Hacia O
		if(delante && !detras){
			angulo = M_PI/4.0; //NO
		}else if(!delante && detras){
			angulo = M_PI/4.0 + M_PI/2.0; //SO
		}else if(!delante && !detras){
			angulo = M_PI/2.0; //O
		}else{
			velocidad = 0.0; //NaN
			modificado = false;
		}
	}else if(!izquierda && !derecha){ //Hacia N o S
		if(delante && !detras){ //Hacia N
			angulo = 0;
		}else if(!delante && detras){ //Hacia S
			angulo = M_PI;
		}else{
			velocidad = 0.0;
			modificado = false;
		}
	}else{ //NaN
		velocidad = 0.0;
		modificado = false;
	}

	//Modificamos la entidad con lo obtenido
	player->setApuntando(c_mapEstado[Apuntando]);
	player->setAnguloMovimiento(angulo);
	player->setVelocidad(velocidad);
	player->setModificado(true);

	//Compruebo que solo se pueda cambiar de pj cada 250 ms
	if(c_mapEstado[CambioPersonajes]){
		long int tiempo = Timer::getTimeElapsed();
		if(tiempo - _cambioPj > 125){
			_cambioPj = tiempo;
			player->switchPersonaje();
		}
	}


	if(c_teclado.isPulsada(Teclado::M))
	{
		CandyNapper::getInstancia()->getEm()->getPlayer()->setModoATope(true);
	}

	if(c_teclado.isPulsada(Teclado::N))
	{
		CandyNapper::getInstancia()->getEm()->getPlayer()->setModoATope(false);
	}

	//TODO: solo es para probar
	/*if(c_teclado.isPulsada(Teclado::E)){
		if(EntityManager::getInstance()->getEnemys().size()>0)
			EntityManager::getInstance()->getEnemys().front()->setVelocidad(5);
	}else{
		if(EntityManager::getInstance()->getEnemys().size() >0)
			EntityManager::getInstance()->getEnemys().front()->setVelocidad(0);
	}*/
}

void
CompKeyboard::copiarDesde(const CompKeyboard & kc){

}

} /* namespace candy */
