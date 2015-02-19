/*
 * Raton.cpp
 *
 *  Created on: 14/02/2012
 *      Author: kaseyo
 */

#include "Raton.h"

namespace candy {

/*
Raton::Raton(Ventana* ventana) {
	c_mapBotones[Izquierdo] = sf::Mouse::Left;
	c_mapBotones[Derecho] = sf::Mouse::Right;
	c_mapBotones[Medio] = sf::Mouse::Middle;

	c_ventanaAsociada = ventana;
}

Raton::~Raton() {

}

Raton::Raton(const Raton & cop){
	copiarDesde(cop);
}

Raton &
Raton::operator =(const Raton & cop){
	if(this != &cop){
		copiarDesde(cop);
	}

	return *this;
}

void
Raton::copiarDesde(const Raton & cop){

}
*/

bool
Raton::isPressed(BotonRaton boton){
	return sf::Mouse::IsButtonPressed((sf::Mouse::Button)boton);
}

Vector2
Raton::getPosition(Ventana* v){
	sf::Vector2i posicionSFML = sf::Mouse::GetPosition(v->c_window);
	Vector2 posicion(posicionSFML.x, posicionSFML.y);

	posicion.setY(v->getHeight() - posicionSFML.y);

	if(posicionSFML.x > v->getWidth() || posicionSFML.x < 0 ||
			posicionSFML.y > v->getHeight() || posicionSFML.y < 0){
		posicion.setX(-1);
		posicion.setY(-1);
	}

	return posicion;
}

void
Raton::setPosition(Vector2 coords, Ventana* v){
	sf::Vector2i posSFML(coords.getX(), v->getHeight() - coords.getY());

	sf::Mouse::SetPosition(posSFML, (sf::Window&)v->c_window);
}

} /* namespace candy */
