/*
 * Raton.h
 *
 *  Created on: 14/02/2012
 *      Author: kaseyo
 */

#ifndef RATON_H_
#define RATON_H_

#include "CandyMath.h"
#include "Ventana.h"
#include "SFML/Window.hpp"
#include <map>
using namespace std;

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */

	/**
	 * @class Raton
	 * @brief Abstraccion del mouse. Es independiente de la ventana
	 * Capa de abstraccion de sf::Mouse, que permite acceder en tiempo real al estado del raton
	 */
	class Raton {
	public:
		enum BotonRaton{
			Izquierdo = sf::Mouse::Left,
			Derecho = sf::Mouse::Right,
			Medio = sf::Mouse::Middle
		};

		/**
		 * Constructor por defecto
		 * @param v Ventana a la que esta asociado el raton
		 */
		/*Raton(Ventana* v);*/

		/**
		 * Destructor por defecto
		 */
		~Raton();

		/**
		 * Constructor de copia de Raton
		 * @param cop Origen de la copia
		 */
		/*Raton(const Raton& cop);*/

		/**
		 * Operador asignacion
		 * @param cop Origen de la copia
		 * @return Referencia al resultado
		 */
		/*Raton& operator=(const Raton& cop);*/

		/**
		 * Indica si un boton esta o no presionado
		 * @param boton Boton que le pasamos (tiene que pertenecer al enum)
		 * @return TRUE si boton esta presionado
		 */
		static bool isPressed(BotonRaton boton);

		/**
		 * Devuelve la posicion del mouse "absoluta" en la ventana
		 * @return Posicion del raton
		 */
		static Vector2 getPosition();

		/**
		 * Devuelve la posicion relativa a la ventana. La posicion la daremos, en coordenadas 2D empezando en la esquina, inferior
		 * izquierda. Si esta fuera de la ventana, la posicion es -1.
		 * @return Posicion relativa a la ventana.
		 */
		static Vector2 getPosition(Ventana* v);

		/**
		 * Settea la posicion del raton a un punto
		 * @param coords Coordenadas
		 */
		static void setPosition(Vector2 coords, Ventana* v);

	private:
		/**
		 * Atributo a la clase Mouse de la SFML
		 */
		/*static sf::Mouse c_mouse;*/

		/**
		 * Ventana a la que esta asociado
		 */
		/*Ventana* c_ventanaAsociada;*/

		/**
		 * Map que relaciona nuestro propio enum con el de la sfml
		 */
		/*map<BotonRaton, sf::Mouse::Button> c_mapBotones;*/

		/**
		 * Funcion auxiliar que copia un objeto en otro.
		 * @param cop Origen de la copia
		 */
		/*void copiarDesde(const Raton& cop);*/
	};

} /* namespace candy */
#endif /* RATON_H_ */
