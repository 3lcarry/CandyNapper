/*
 * CompMusic.h
 *
 *  Created on: 12/05/2012
 *      Author: esteve
 */

#ifndef COMPMUSIC_H_
#define COMPMUSIC_H_

#include "IComponent.h"
#include "GameEntity.h"
#include "GEDynamic.h"
#include "Timer.h"
#include "InterfazMusic.h"
#include "Player.h"
#include "Teclado.h"

namespace candy {

class CompMusic: public candy::IComponent {
private:
	GameEntity* _emisor;
	struct Sonidos {
		int ID;
		int lastTime;
		Sonidos(int id, int time) {
			ID = id;
			lastTime = time;
		}
	};
	bool TimePassed(Sonidos &sonido, int time);
	InterfazMusic* _IM;
	enum sonidos {
		Pasos,
		AtaqueEnemigo,
		AtaqueHans,
		AtaqueGreta
	};
	map<int, Sonidos> _sonidos;

public:
	CompMusic(GameEntity *emisor);
	~CompMusic();
	void Update(GameEntity* entity);
};

}

#endif /* COMPMUSIC_H_ */
