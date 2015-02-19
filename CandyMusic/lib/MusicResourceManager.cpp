/*
 * MusicResourceManager.cpp
 *
 *  Created on: 04/05/2012
 *      Author: esteve
 */

#include "MusicResourceManager.h"

namespace candy {

MusicResourceManager::MusicResourceManager(){
	croot = CANDYMUSICROOT;
}

MusicResourceManager::~MusicResourceManager(){

}

void MusicResourceManager::AddSound(int ID, string nom){
	SoundBuffer *sbuffer = new SoundBuffer();
	if(!sbuffer->LoadFromFile(croot + nom))
		throw("Error, el fichero " + nom + " no se puede abrir");
	else
		_sounds.insert(pair<int, SoundBuffer*>(ID, sbuffer));

}

void MusicResourceManager::AddMusic(int ID, string nom){
	Music *music = new Music();
	if(!music->OpenFromFile(croot + nom))
		throw("Error, el fichero " + nom + " no se puede abrir");
	else
		_musics.insert(pair<int, Music*>(ID, music));

}

Music* MusicResourceManager::getMusic(int ID){
	Music *music = new Music();
	_itMusic = _musics.find(ID);
	if(_itMusic != _musics.end()){
		music = _itMusic->second;
	}
	else {
		ostringstream oss(ostringstream::out);
		oss <<"Error, la ID "<<ID<<" no existe"<<endl;
		throw(oss.str());
	}

	return music;
}

SoundBuffer* MusicResourceManager::getSoundBuffer(int ID){
	SoundBuffer *sbuffer = new SoundBuffer();
	_itSound = _sounds.find(ID);
	if(_itSound != _sounds.end()){
		sbuffer = _itSound->second;
	}
	else {
		ostringstream oss(ostringstream::out);
		oss <<"Error, la ID "<<ID<<" no existe"<<endl;
		throw(oss.str());
	}

	return sbuffer;
}

}
