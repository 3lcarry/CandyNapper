/*
 * MusicEngine.h
 *
 *  Created on: 28/04/2012
 *      Author: esteve
 */

#ifndef MUSICENGINE_H_
#define MUSICENGINE_H_

#include <iostream>
#include <vector>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "MusicResourceManager.h"
#include "CandyMath.h"
using namespace std;
using namespace sf;

namespace candy {

class MusicEngine {
friend class InterfazMusic;
private:
	/**
	 * Objeto del gestor de recursos de musica
	 */
	MusicResourceManager _mrm;

	/**
	 * Aqui se almacenaran los sonido que se esten utilizando
	 */
	map<int, Sound*>  _sounds;

	/**
	 * Aqui se almacena la musica actual
	 */
	Music *_music;

	/**
	 * Iterador de sonidos
	 */
	map<int, Sound* >::iterator _itSounds;

	int _IDSound;

	int _soundVolumePercent;

public:
	/**
	 * Constructor por defecto
	 */
	MusicEngine();

	/**
	 * Destructor
	 */
	~MusicEngine();

	/**
	 * Carga una serie de canciones en el gestor de recursos de sondios
	 * @param map donde el int representa el ID y el string el nombre del fichero
	 */
	void LoadMusic(map<int, string>);

	/**
	 * Carga una musica en el gestor de recursos de sonidos
	 * @param entero que representa la ID
	 * @param string nombre del fichero a cargar.
	 */
	void LoadMusic(int, string);

	/**
	 * Cargar un sonido en el gestro de recursos de musica
	 * @param nombre del sonido a cargar
	 */
	int LoadSound(string nom);

	/**
	 * Play de la música
	 * @param ID de la música, si no se pasa un ID se reproduce la musica anterior
	 */
	void M_Play(int ID = -1);

	/**
	 * Pause de la musica actual
	 */
	void M_Pause();

	/**
	 * Stop de la musica actual
	 */
	void M_Stop();

	/**
	 * Play de un sonido
	 * Si no esta en el map lo añade
	 * @param identificador de la entidad
	 */
	void S_Play(int ID);

	/**
	 * Pause de un sonido
	 * @param identificador de la entidad
	 */
	void S_Pause(int ID);

	/**
	 * Stop de un sonido
	 * @param identificador de la entidad
	 * @param nombre del sonido
	 */
	void S_Stop(int ID);

	/**
	 * Indica si el sonido se repite o no
	 * @param ID del sonido
	 * @param boleano que indica si hay bucle o no
	 */
	void S_Loop(int ID, bool loop);

	/**
	 * Establece la posición de un sonido
	 * @param identificador de la entidad
	 * @param coordenadas del sonido
	 */
	void S_Position(int ID, Vector3 pos);

	/**
	 * Establece la posición de un sonido
	 * @param identificador de la entidad
	 * @param coordenada X
	 * @param coordenada Y
	 * @parma coordenada Z
	 */
	void S_Position(int ID, float x, float y, float z);

	/**
	 * Establece la atenuación de un sonido
	 * @param ID del sonido
	 * @param Grado de atenuación
	 */
	void S_Atenuation(int ID, float attenuation);

	/**
	 * Establece la distancia hasta la que se oye el sonido sin atenuación
	 * @param ID del sonido
	 * @param Distancia sin atenuación
	 */
	void S_MinDist(int ID, float dist);

	/**
	 * Se le añaden todas la propiedades del sonido
	 * @param ID del sonido
	 * @param Indica si se quiere un bucle en el sonido o no
	 * @param Establece la posición del sonido
	 * @param Establece el grado de atenuación del sonido
	 * @param Establece la distancia hasta la que se oye el sonido sin atenuación
	 */
	void S_Properties(int ID, bool loop, Vector3 position, float attenuation, float minDist);

	/**
	 * Se indica la posición del listener
	 * @param vector con las coordenadas
	 */
	void setPosListener(Vector3 pos);

	/**
	 * Se indica la posición del listener
	 * @param coordenada X
	 * @param coordenada Y
	 * @param coordenada Z
	 */
	void setPosListener(float x, float y, float z);

	/**
	 * Se indica un nuevo valor para el volumen global de juego;
	 * @param volumen
	 */
	void setGlobalVolume(int vol);

	/**
	 * Se indica un nuevo valor de volumen para un sonido
	 * @param ID del sonido
	 * @param volumen
	 */
	void setSoundVolume(int ID, int vol);

	/**
	 * Se indica un nuevo valor de volumen para una musica
	 * @param ID de la musica
	 * @param volumen
	 */
	void setMusicVolume(int vol);

	/**
	 * Indica si un sonido se esta reproduciendo
	 * @param ID del sonido que se quiere consultar
	 * @return boleano
	 */
	bool S_IsPlaying(int ID);

	/**
	 * Sirve para aumentar o disminuir el volumen
	 * @param volumen
	 */
	void ChangeSoundVolume(float v);

	void ChangeMusicVolume(float v);

	void ChangeGlobalVolume(float v);

};

}

#endif /* MUSICENGINE_H_ */
