/*
 * CompPlayer.cpp
 *
 *  Created on: 11/05/2012
 *      Author: carrillo
 */

#include "CompPlayer.h"
#include "Player.h"
#include "Timer.h"
#include "InterfazGraphics.h"
#include "InterfazMusic.h"
#include "HUD.h"
#include <sstream>

namespace candy {

CompPlayer::CompPlayer() {
	Atope = false;
	inicioAtope = 0;
	dirMensaje = 1;
}

CompPlayer::~CompPlayer() {
	// TODO Auto-generated destructor stub

}

void CompPlayer::Update(GameEntity *entidad) {
	Player* p = ((Player*) entidad);

	int vida  = p->getVidaRestante();
	Text* mensajeAtope = InterfazGraphics::getInstance()->getHUD()->getMensajeCentral();

	if(p->getModoATope())
	{
		if(!Atope)
		{
			//La primera vez que esta en a tope activar musica
			InterfazMusic::getInstancia()->desactivarMusicaFondo();
			if(InterfazMusic::getInstancia()->WhatMusic() != InterfazMusic::Atope){
				InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Atope);
				InterfazMusic::getInstancia()->setVolumenMusicaFondo(60);
			}
			mensajeAtope->setFontAnimated(20,40,1000);
			inicioAtope = Timer::getTimeElapsed();
			mensajeAtope->setActive(true);
		}
		Atope = true;
		p->getAttack()->setModificador(5.0);
		p->setModificadorVelocidad(3.0);

		int tiempoRestante = 60000 - (Timer::getTimeElapsed() - inicioAtope);
		tiempoRestante /= 1000;
		//mensajeAtope->setTamanyo(mensajeAtope->getTamanyo()+dirMensaje);

		ostringstream oss(ostringstream::out);
		oss << "A TOPE " << tiempoRestante << " SEGUNDOS";

		mensajeAtope->setTexto(oss.str());
		if(tiempoRestante <= 0)
		{
			p->setModoATope(false);
		}
	}
	else
	{
		if(Atope)
		{
			//Sale de Atope, activar musica normal
			InterfazMusic::getInstancia()->desactivarMusicaFondo();
			if(InterfazMusic::getInstancia()->WhatMusic() != InterfazMusic::Juego){
				InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Juego);
				InterfazMusic::getInstancia()->setVolumenMusicaFondo(60);
			}
			mensajeAtope->setActive(false);
		}
		Atope = false;
		p->getAttack()->setModificador(1.0);
		p->setModificadorVelocidad(1.0);
	}

}

} /* namespace candy */
