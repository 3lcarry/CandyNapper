/*
 * InterfazMusic.cpp
 *
 *  Created on: 10/05/2012
 *      Author: esteve
 */

#include "InterfazMusic.h"

namespace candy {

InterfazMusic* InterfazMusic::referencia = NULL;

InterfazMusic*
InterfazMusic::getInstancia() {
	if(referencia == NULL)
	{
		referencia = new InterfazMusic();
	}
	return referencia;
}

MusicEngine*
InterfazMusic::getMusicEngine() {
	return mEngine;
}

InterfazMusic::InterfazMusic() {
	// TODO Auto-generated constructor stub
	mEngine = new MusicEngine();
	_IDMusicPlaying = 0;
	mEngine->LoadMusic(Fondo, "music.ogg");
	mEngine->LoadMusic(Juego, "FondoGame.ogg");
	mEngine->LoadMusic(Atope, "Hey-jude.ogg");

}

InterfazMusic::~InterfazMusic() {
	// TODO Auto-generated destructor stub
	if(mEngine != NULL)
	{
		delete mEngine;
	}
}



void
InterfazMusic::activarMusicaFondo(InterfazMusic::Musica id) {
	mEngine->M_Play(id);
	_IDMusicPlaying = id;
}


void InterfazMusic::desactivarMusicaFondo(){
	mEngine->M_Stop();
}


void InterfazMusic::setVolumenMusicaFondo(int volumen){
	mEngine->setMusicVolume(volumen);
}


void InterfazMusic::setVolumenEfecSonido(int volumen){
	map<int, Sound* >::iterator it;
	for(it = mEngine->_sounds.begin(); it != mEngine->_sounds.end(); it++) {
		mEngine->setSoundVolume(it->first, volumen);
	}

}


void InterfazMusic::setVolumenGlobal(int volumen){
	mEngine->setGlobalVolume(volumen);
}


int InterfazMusic::AddSonido(Sonidos tipo){
	int id;

	switch(tipo){
		case Pasos: id= mEngine->LoadSound("Step.wav");
		break;
		case AtaqueEnemigo: id = mEngine->LoadSound("hit.wav");
		break;
		case AtaqueHans: id = mEngine->LoadSound("AttackHans.wav");
		break;
		case AtaqueGreta: id = mEngine->LoadSound("AttackGreta.wav");
		break;
		case Bird: id = mEngine->LoadSound("Bird.wav");
		break;
	}

	return id;
}

int InterfazMusic::WhatMusic() {
	return _IDMusicPlaying;
}

}
