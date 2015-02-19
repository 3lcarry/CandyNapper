/*
 * MusicResourceManager.h
 *
 *  Created on: 04/05/2012
 *      Author: esteve
 */

#ifndef MUSICRESOURCEMANAGER_H_
#define MUSICRESOURCEMANAGER_H_

#include <iostream>
#include <vector>
#include <sstream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
using namespace std;
using namespace sf;

namespace candy {

/**
 * @class MusicReourceManager
 * @brief Gestor de recursos de musica
 */
class MusicResourceManager {

private:
	/**
	 * Ruta en la que se encuentran los archivos de audio
	 */
	string croot;

	/**
	 * Almacena los bufferes de sonido por su ID
	 */
	map<int, SoundBuffer*> _sounds;

	/**
	 * Almacena la musica por su ID
	 */
	map<int , Music*> _musics;

	/**
	 * Iterador de _sounds
	 */
	map<int, SoundBuffer*>::iterator _itSound;

	/**
	 * Iterador de musics
	 */
	map<int, Music*>::iterator _itMusic;

public:
	/**
	 * Constructor por defecto
	 */
	MusicResourceManager();

	/**
	 * Destructor
	 */
	~MusicResourceManager();

	/**
	 * Añade un sonido a _sounds
	 * @param ID del sonido
	 * @param nombre del archivo de sonido
	 */
	void AddSound(int ID, string nomFic);

	/**
	 * Añade un objeto Music al _musics
	 * @param ID de la música
	 * @param nombre del archivo de música
	 */
	void AddMusic(int ID, string nomFic);

	/**
	 * Devuelve un puntero a un objeto Music a partir de su nombre de fichero
	 * @param ID de la música
	 * @return puntero de Music
	 */
	Music* getMusic(int ID);

	/**
	 * Devuelve un puntero a un objeto SoundBuffer a partir de su nombre de fichero
	 * @param ID del sonido
	 * @return puntero de SondBuffer
	 */
	SoundBuffer* getSoundBuffer(int ID);
};

}

#endif /* MUSICRESOURCEMANAGER_H_ */
