/*
 * CompGraphicPlayer.cpp
 *
 *  Created on: 20/02/2012
 *      Author: kaseyo
 */

#include "CompGraphicPlayer.h"
#include "GEDynamic.h"
#include "CandyMath.h"
#include "GameEntity.h"
#include "Player.h"
#include "World3D.h"
#include "Timer.h"

namespace candy {

Vector3 CompGraphicPlayer::c_normalCentro(0, 4.0, 15);
Vector3 CompGraphicPlayer::c_normalReferencia(0, 0, -15);
Vector3 CompGraphicPlayer::c_normalUp(0, 1, 0);

Vector3 CompGraphicPlayer::c_apuntandoCentro(0, 2.0, 10);
Vector3 CompGraphicPlayer::c_apuntandoReferencia(0, 0, -50);
Vector3 CompGraphicPlayer::c_apuntandoUp(0, 1, 0);

CompGraphicPlayer::CompGraphicPlayer(GameEntity* entidad)
{
	InterfazGraphics* ig = InterfazGraphics::getInstance();

	//Nos guardamos la transformacion de la escena (TENER EN CUENTA QUE SU ORDER=TRUE)
	c_tEscena = ig->getWorld3D()->getScene3D();

	_tSky = ig->getWorld3D()->getSky();

	//Anyadimos la transformacion del player a la global de la camera
	c_tplayer = ig->getWorld3D()->getDirector()->addTransformation();
	particulas = c_tplayer->addParticles();
	c_tplayer->Translate(-1.5, 0, 0);

	particulas->setActive(false);


	//Creamos el player con su modelo y su textura
	c_mplayer = c_tplayer->addModel(InterfazGraphics::M_Chico, InterfazGraphics::T_Chico);

	_modelTio = InterfazGraphics::M_Chico;
	_modelTia = InterfazGraphics::M_Chica;

	vector<int> modelos;
	for(int i=InterfazGraphics::M_ChicoMovimiento1; i<=InterfazGraphics::M_ChicoMovimiento12;i++){
		modelos.push_back(i);
	}

	_movimientoTio.setModel(c_mplayer);
	_movimientoTio.addModels(modelos);

	modelos.clear();

	for(int i=InterfazGraphics::M_ChicoAtaque1; i<=InterfazGraphics::M_ChicoAtaque11;i++){
		modelos.push_back(i);
	}
	_ataqueTio.setModel(c_mplayer);
	_ataqueTio.addModels(modelos);

	modelos.clear();

	for(int i=InterfazGraphics::M_ChicaMovimiento1; i<=InterfazGraphics::M_ChicaMovimiento5;i++){
		modelos.push_back(i);
	}
	_movimientoTia.setModel(c_mplayer);
	_movimientoTia.addModels(modelos);

	modelos.clear();

	for(int i=InterfazGraphics::M_ChicaAtaque; i<=InterfazGraphics::M_ChicaAtaque;i++){
		modelos.push_back(i);
	}
	_ataqueTia.setModel(c_mplayer);
	_ataqueTia.addModels(modelos);

	//Lo ponemos a true para que se encargue el de inicializar la pos del director y de la mirilla
	//(asi evitamos duplicar datos en dos ficheros)
	c_apuntandoSetted = true;

	c_hansSetted = true;

	//Actualizamos el componente grafico (lo "inicializamos")
	Player* ent_din = (Player*) entidad;
	actualizar(ent_din);
}

CompGraphicPlayer::~CompGraphicPlayer() {
	c_tplayer->setDestroy(true);
}

void
CompGraphicPlayer::Update(GameEntity* entidad){
	Player* ent_din = (Player*) entidad;

	if(ent_din->isModificado()){
		actualizar(ent_din);
	}

	//cout << "Modelo en Uso Realmente: " <<c_mplayer->getIdModel() << endl;
}

void
CompGraphicPlayer::actualizar(Player* player){
	Vector3 pos_player = player->getPosicion();


	Vector3 inversa(-pos_player.getX(), pos_player.getY(), -pos_player.getZ());

	//Calculamos el eje sobre el que rotamos el angulo de vision Y
	Vector3 eje_x(cos(player->getVisionX()), 0, sin(player->getVisionX()));

	c_tEscena->setRotation(eje_x, player->getVisionY());
	c_tEscena->Rotate(1, -player->getVisionX());

	_tSky->setRotation(eje_x, player->getVisionY() / 2.0);
	_tSky->Rotate(1, -player->getVisionX());

	c_tEscena->setTranslation(inversa);

	if(player->isHans()){
		if(!c_hansSetted){
			c_hansSetted = true;
			c_mplayer->setTexture(InterfazGraphics::T_Chico);
		}
	}else{
		if(c_hansSetted){
			c_hansSetted = false;
			c_mplayer->setTexture(InterfazGraphics::T_Chica);
		}
	}


	if(player->getModoATope())
	{
		particulas->setActive(true);
	}else{
		particulas->setActive(false);
	}

	//Elegimos el modelo a utilizar, si la animacion o la defecto y tio o tia
	if(player->isHans()){
		if(player->getVelocidad()!=0){
			if(player->getModoATope())
				_movimientoTio.Continue(250);
			else
				_movimientoTio.Continue();
			_movimientoTia.Start();
		}
		else if(player->isAttacking()){
			_atacandoTio = true;
		}else{
			_movimientoTio.Start();
			_movimientoTia.Start();
			c_mplayer->setIdModel(_modelTio);
			_atacandoTio = false;
		}

		if(_atacandoTio)
		{
			_ataqueTio.Continue(500);

			if(Timer::getTimeElapsed() - _utlimoAtaque > 500){
				_utlimoAtaque = Timer::getTimeElapsed();
				_atacandoTio = false;
				_ataqueTio.Start();
			}
		}

	}else{
		if(player->getVelocidad()!=0){
			if(player->getModoATope())
				_movimientoTia.Continue(250);
			else
				_movimientoTia.Continue();
			_movimientoTio.Start();
		}
		else if(player->isAttacking()){
			_atacandoTia = true;
		}
		else{
			_movimientoTia.Start();
			_movimientoTio.Start();
			c_mplayer->setIdModel(_modelTia);
			_atacandoTia = false;
		}

		if(_atacandoTia)
		{
			_ataqueTia.Continue(500);

			if(Timer::getTimeElapsed() - _utlimoAtaque > 500){
				_utlimoAtaque = Timer::getTimeElapsed();
				_atacandoTia = false;
				_ataqueTia.Start();
			}
		}
	}


	if(player->isApuntando()){
		if(!c_apuntandoSetted){
			c_apuntandoSetted = true;
			Director* dir = InterfazGraphics::getInstance()->getWorld3D()->getDirector();

			dir->setCenter(c_apuntandoCentro);
			dir->setReference(c_apuntandoReferencia);
			dir->setUp(c_apuntandoUp);

			//PENDIENTE DE IMPLEMENTACION
			//InterfazGraphics::getInstance()->getMirillaTransformation()->Translate(0, -150);
		}
	}else{
		if(c_apuntandoSetted){
			c_apuntandoSetted = false;
			Director* dir = InterfazGraphics::getInstance()->getWorld3D()->getDirector();

			dir->setCenter(c_normalCentro);
			dir->setReference(c_normalReferencia);
			dir->setUp(c_normalUp);

			//PENDIENTE DE IMPLEMENTACION
			//InterfazGraphics::getInstance()->getMirillaTransformation()->Translate(0, 150);
		}
		//c_tplayer->setRotation(0, -player->getVisionY());
		c_tplayer->setRotation(1, player->getAnguloMovimiento());
	}

}

} /* namespace candy */
