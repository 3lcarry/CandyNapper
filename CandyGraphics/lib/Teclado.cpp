/*
 * EventoTeclado.cpp
 *
 *  Created on: 07/11/2011
 *      Author: kaseyo
 */

#include "Teclado.h"

namespace candy{

/*
Teclado::Teclado(){
	/*
	c_map_teclas[W] = sf::Keyboard::W;
	c_map_teclas[A] = sf::Keyboard::A;
	c_map_teclas[S] = sf::Keyboard::S;
	c_map_teclas[D] = sf::Keyboard::D;
	c_map_teclas[RAlt] = sf::Keyboard::RAlt;


	for(int i = 0; i < NumTeclas; i++){
		c_map_teclas[Tecla(i)] = sf::Keyboard::Key(i);
	}
}


Teclado::~Teclado(){

}

Teclado::Teclado(const Teclado &cop){
	copiarDesde(cop);
}

Teclado&
Teclado::operator=(const Teclado& cop){
	if(this != &cop){
		copiarDesde(cop);
	}

	return *this;
}

void
Teclado::copiarDesde(const Teclado& cop){
	c_map_teclas = cop.c_map_teclas;
}
*/
bool
Teclado::isPulsada(Tecla tecla){
	return sf::Keyboard::IsKeyPressed(sf::Keyboard::Key(tecla));
}

}
