#include "EntityManager.h"
//#include "InOut.h"
#include <iostream>
#include <SFML/Window.hpp>

using namespace std;
using namespace candy;

void
showPlayerStats(GEDynamic* myplayer){
	cout << "Angulo: " << myplayer->getVisionX() << " Velocidad: " << myplayer->getVelocidad() << endl;
}

int main(){
	/*
	EntityManager em(0, 0);
	GEDynamic* player = (GEDynamic*)em.getPlayer();
	InOut inout;
	Ventana window(800, 600);

	inout.Init(&em);

	while(!window.getCerrar()){
		window.Update();
		em.Update();
		showPlayerStats(player);
		window.Display();
	}

	return 0;
	*/
}
