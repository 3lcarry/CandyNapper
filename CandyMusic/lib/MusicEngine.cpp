/*
 * MusicEngine.cpp
 *
 *  Created on: 28/04/2012
 *      Author: esteve
 */

#include "MusicEngine.h"

namespace candy {

MusicEngine::MusicEngine(){
	_IDSound = 0;
	_music = NULL;
	_soundVolumePercent = 80;
}


MusicEngine::~MusicEngine(){
	_music = NULL;
}


void MusicEngine::LoadMusic(map<int, string> music){
	map<int, string>::iterator it;

	for(it = music.begin(); it != music.end(); it++){
		try {
			_mrm.AddMusic(it->first, it->second);
		}
		catch(string s) {
			cout<<s<<endl;
		}
	}
}


void MusicEngine::LoadMusic(int ID, string nom){
	try {
		_mrm.AddMusic(ID, nom);
	}
	catch(string s) {
		cout<<s<<endl;
	}
}


int MusicEngine::LoadSound(string nom){
	_IDSound++;
	try {
		_mrm.AddSound(_IDSound, nom);
		SoundBuffer* sb =_mrm.getSoundBuffer(_IDSound);
		Sound* s = new Sound(*sb);
		_sounds.insert(pair<int,Sound*>(_IDSound,s));
	}
	catch(string s) {
		cout<<s<<endl;
	}

	return _IDSound;
}


void MusicEngine::M_Play(int ID){


	if(ID != -1) {
		Music* aux = _mrm.getMusic(ID);
		if(_music == NULL || (_music->GetStatus() != Sound::Playing && aux != _music)){
			M_Stop();
			_music = _mrm.getMusic(ID);
			_music->Play();
		}
	}
	else if(ID == -1 && _music == NULL)
		cout<<"MusicEngine: Error en M_Play"<<endl;
	//_music->Play();

}


void MusicEngine::M_Pause(){
	if(_music != NULL)
		_music->Pause();
}


void MusicEngine::M_Stop(){
	if(_music != NULL)
		_music->Stop();
}


void MusicEngine::S_Play(int ID){
	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end())
	{
		_itSounds->second->Play();
	}
}


void MusicEngine::S_Pause(int ID){
	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end())
		_itSounds->second->Pause();
}


void MusicEngine::S_Stop(int ID){
	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end())
		_itSounds->second->Stop();
}

void MusicEngine::S_Loop(int ID, bool loop){
	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end())
		_itSounds->second->SetLoop(loop);
}

void MusicEngine::S_Position(int ID, Vector3 pos){
	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end())
		_itSounds->second->SetPosition(pos.getX(), pos.getY(), pos.getZ());
}


void MusicEngine::S_Position(int ID, float x, float y, float z){
	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end())
		_itSounds->second->SetPosition(x, y, z);
}

void MusicEngine::S_Atenuation(int ID, float attenuation){
	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end())
	{
		_itSounds->second->SetAttenuation(attenuation);
	}
}

void MusicEngine::S_MinDist(int ID, float dist){
	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end())
		_itSounds->second->SetMinDistance(dist);
}

void MusicEngine::S_Properties(int ID, bool loop, Vector3 pos, float attenuation, float dist){
	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end()){
		_itSounds->second->SetLoop(loop);
		_itSounds->second->SetPosition(pos.getX(), pos.getY(), pos.getZ());
		_itSounds->second->SetAttenuation(attenuation);
		_itSounds->second->SetMinDistance(dist);
	}
}


void MusicEngine::setPosListener(Vector3 pos){
	Listener::SetPosition(pos.getX(), pos.getY(), pos.getZ());
}


void MusicEngine::setPosListener(float x, float y, float z){
	Listener::SetPosition(x, y, z);
}

void MusicEngine::setGlobalVolume(int vol) {
	Listener::SetGlobalVolume(vol);
}

void MusicEngine::setSoundVolume(int ID, int vol){

	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end()){
		_itSounds->second->SetVolume(vol);
	}
}

void MusicEngine::setMusicVolume(int vol) {

	if(_music != NULL) {
		_music->SetVolume(vol);
	}

}

bool MusicEngine::S_IsPlaying(int ID) {

	_itSounds = _sounds.find(ID);
	if(_itSounds != _sounds.end()){
		if(_itSounds->second->GetStatus() == Sound::Playing){
			return true;
		}
	}
	return false;
}

void MusicEngine::ChangeSoundVolume(float v) {

	for(_itSounds = _sounds.begin(); _itSounds != _sounds.end(); _itSounds++){
		_itSounds->second->SetVolume(_itSounds->second->GetVolume() + v);
		cout<< "MusicEngine: "<<_itSounds->second->GetVolume()<<endl;
	}
}

void MusicEngine::ChangeMusicVolume(float v) {
	_music->SetVolume(_music->GetVolume() + v);
	cout<<"volumen musica: "<<_music->GetVolume()<<endl;
}

void MusicEngine::ChangeGlobalVolume(float v) {
	Listener::SetGlobalVolume(Listener::GetGlobalVolume() + v);
}



}
