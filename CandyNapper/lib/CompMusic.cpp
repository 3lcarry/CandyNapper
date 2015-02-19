/*
 * CompMusic.cpp
 *
 *  Created on: 12/05/2012
 *      Author: esteve
 */

#include "CompMusic.h"

namespace candy {

bool CompMusic::TimePassed(Sonidos &sonido, int time){
	if((Timer::getTimeElapsed() - sonido.lastTime) > time) {
		sonido.lastTime = Timer::getTimeElapsed();
		return true;
	}
	return false;
}

CompMusic::CompMusic(GameEntity* emisor) {
		_emisor = emisor;
		_IM = InterfazMusic::getInstancia();
		int id = -1;
		_sonidos.insert(pair<int,Sonidos>(CompMusic::Pasos,Sonidos(id = _IM->AddSonido(InterfazMusic::Pasos),0)));
		if(id != -1)
			_IM->getMusicEngine()->setSoundVolume(id, 90);

		_sonidos.insert(pair<int, Sonidos>(CompMusic::AtaqueEnemigo, Sonidos(id = _IM->AddSonido(InterfazMusic::AtaqueEnemigo),0)));

		_sonidos.insert(pair<int, Sonidos>(CompMusic::AtaqueHans, Sonidos(id = _IM->AddSonido(InterfazMusic::AtaqueHans),0)));
		_sonidos.insert(pair<int, Sonidos>(CompMusic::AtaqueGreta, Sonidos(id = _IM->AddSonido(InterfazMusic::AtaqueGreta),0)));
}

CompMusic::~CompMusic() {
	// TODO Auto-generated destructor stub
}

void CompMusic::Update(GameEntity* entity) {

	///VOLUMEN DESDE TECLADO///
	if(Teclado::isPulsada(Teclado::Add) && Teclado::isPulsada(Teclado::LControl) && Teclado::isPulsada(Teclado::LShift)) {
		_IM->getMusicEngine()->ChangeMusicVolume(1);
	}
	else if(Teclado::isPulsada(Teclado::Subtract) && Teclado::isPulsada(Teclado::LControl) && Teclado::isPulsada(Teclado::LShift)) {
		_IM->getMusicEngine()->ChangeMusicVolume(-1);
	}
	else if(Teclado::isPulsada(Teclado::Add) && Teclado::isPulsada(Teclado::LControl)){
		_IM->getMusicEngine()->ChangeSoundVolume(1);
	}
	else if(Teclado::isPulsada(Teclado::Subtract) && Teclado::isPulsada(Teclado::LControl)){
		_IM->getMusicEngine()->ChangeSoundVolume(-1);
	}
	else if(Teclado::isPulsada(Teclado::Add)){
		_IM->getMusicEngine()->ChangeGlobalVolume(0.1);
	}
	else if(Teclado::isPulsada(Teclado::Subtract)) {
		_IM->getMusicEngine()->ChangeGlobalVolume(-0.1);
	}


	///REPRODUCCION DE SONIDOS///
	if(_emisor->getTipo() == GameEntity::Player){
		_IM->getMusicEngine()->setPosListener(_emisor->getPosicion());
	}

	if(_emisor->getTipo() == GameEntity::Player || _emisor->getTipo() == GameEntity::Enemigo) {
		map<int, Sonidos>::iterator it;

		it = _sonidos.find(CompMusic::Pasos);


		if(it != _sonidos.end()){
			int id = it->second.ID;
			_IM->getMusicEngine()->S_Position(id,_emisor->getPosicion());
			_IM->getMusicEngine()->S_Atenuation(id, 0.5);
			_IM->getMusicEngine()->S_MinDist(id, 5.0);

			int time = 500;
			if(_emisor->getTipo() == GameEntity::Player && ((Player*)_emisor)->getModoATope())
				time = 150;



			if(TimePassed(it->second, time) && !(_IM->getMusicEngine()->S_IsPlaying(id)) && ((GEDynamic*)_emisor)->getVelocidad() > 0.0) {
				_IM->getMusicEngine()->S_Play(id);
			}
		}


		if(_emisor->getTipo() == GameEntity::Enemigo && ((GEDynamic*)_emisor)->getAttack()->isAttacking()){
			it = _sonidos.find(CompMusic::AtaqueEnemigo);

			if(it != _sonidos.end()) {
				int id = it->second.ID;
				_IM->getMusicEngine()->S_Position(id,_emisor->getPosicion());

				if(!(_IM->getMusicEngine()->S_IsPlaying(id)))
					_IM->getMusicEngine()->S_Play(id);
			}
			//((GEDynamic*)_emisor)->getAttack()->isAttacking(false);
		}
		else if(_emisor->getTipo() == GameEntity::Player) {
			if(((Player*)_emisor)->isAttacking()) {
				if(((Player*)_emisor)->isHans())
					it = _sonidos.find(CompMusic::AtaqueHans);
				else
					it = _sonidos.find(CompMusic::AtaqueGreta);

				if(it != _sonidos.end()) {
					int id = it->second.ID;
					_IM->getMusicEngine()->S_Position(id,_emisor->getPosicion());

					if(!(_IM->getMusicEngine()->S_IsPlaying(id)))
						_IM->getMusicEngine()->S_Play(id);
				}
			}
		}
	}
}

}
