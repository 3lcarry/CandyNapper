/*
 * InterfazMusic.h
 *
 *  Created on: 10/05/2012
 *      Author: esteve
 */

#ifndef INTERFAZMUSIC_H_
#define INTERFAZMUSIC_H_
#include "MusicEngine.h"

namespace candy {

enum Musica{
	Fondo
};

class InterfazMusic {

private:
	InterfazMusic();
	MusicEngine *mEngine;
	static InterfazMusic* referencia;
	int _IDMusicPlaying;

public:
	enum Musica{
		Menu,
		Juego,
		Atope
	};

	enum Sonidos {
		Pasos,
		AtaqueEnemigo,
		AtaqueHans,
		AtaqueGreta,
		Bird
	};

	/**
	 * Destructor
	 */
	~InterfazMusic();

	/**
	 * Devuelve un punture objeto del motor para profundizar más
	 * @preturn puntero a MusicEngine
	 */
	MusicEngine* getMusicEngine();

	/**
	 * Devuelve una instancia de la interfaz
	 * @param puntero a la propia interfaz
	 */
	static InterfazMusic* getInstancia();

	/**
	 * Activa la musica de fondo
	 * @param enum con la musica que se desea
	 */
	void activarMusicaFondo(InterfazMusic::Musica id);

	/**
	 * Desactiva la musica de fondo
	 */
	void desactivarMusicaFondo();

	/**
	 * Se indica el volmen de la música de fondo
	 * @param volumen
	 */
	void setVolumenMusicaFondo(int volumen);

	/**
	 * Se indica el volumen de los efectos de sonido
	 * @param volumen
	 */
	void setVolumenEfecSonido(int volumen);

	/**
	 * Se indica el volumen global del juego
	 * @param volumen
	 */
	void setVolumenGlobal(int volumen);

	/**
	 *	Añade un sondio y te devuelve el ID del sonido
	 *	@param enun de tipo sonido
	 *	@return ID del sonido
	 */
	int AddSonido(Sonidos tipo);

	/**
	 * Devuelve el id de la musica que esta reproduciendo
	 * @return ID
	 */
	int WhatMusic();

};



}

#endif /* INTERFAZMUSIC_H_ */
