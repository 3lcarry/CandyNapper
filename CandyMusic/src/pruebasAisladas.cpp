/*
 * pruebasAisladas.cpp
 *
 *  Created on: 28/04/2012
 *      Author: esteve
 */

#include "MusicEngine.h"

using namespace sf;
//string croot=CANDYMUSICROOT;

void PlaySound(sf::Sound& Sound) {
    // Start the sound
    Sound.Play();

    // Loop while the sound is playing
    while (Sound.GetStatus() == sf::Sound::Playing)
    {
        // Leave some CPU time for other processes
		sf::Sleep(sf::Seconds(3));
    }
}

string croot=CANDYMUSICROOT;

int main() {

	SoundBuffer sbuffer;
	sbuffer.LoadFromFile(croot + "Rain_wind.wav");
	Sound sound(sbuffer);
	sound.SetPosition(0.f, 0.f, 0.f);
	sound.SetRelativeToListener(false);
	sound.SetMinDistance(50.f);
	sound.SetAttenuation(0.5);

	//Listener::SetPosition(0.f, 0.f, 0.f);
	//Listener::SetGlobalVolume(80);


	for(int i = 0; i <= 100; i+=100) {
		cout<<"Listener Pos: ("<<i<<", 0, 0)"<<endl;
		Listener::SetPosition((float)i, 0.f, 0.f);
		PlaySound(sound);
	}
	Listener::SetPosition(2000, 2000.f, 0.f);
    // Start the sound
    sound.Play();

    // Loop while the sound is playing
    while (sound.GetStatus() == sf::Sound::Playing)
    {
        // Leave some CPU time for other processes
		sf::Sleep(sf::Seconds(3));
    }


 }
