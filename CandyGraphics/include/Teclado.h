/*
 * EventoTeclado.h
 *
 *  Created on: 07/11/2011
 *      Author: kaseyo
 */

#ifndef TECLADO_H_
#define TECLADO_H_

#include "SFML/Window.hpp"
#include <map>
using namespace std;


namespace candy {

	/**
	 * @class Teclado
	 * @brief Gestor de eventos de teclado
	 * Se encarga de gestionar todos los eventos de teclado.
	 */
	class Teclado {
	public:
		/**
		 * Enum con los tipos de acciones posibles
		 */
		enum Tecla{
			  A,
			  B,
			  C,
			  D,
			  E,
			  F,
			  G,
			  H,
			  I,
			  J,
			  K,
			  L,
			  M,
			  N,
			  O,
			  P,
			  Q,
			  R,
			  S,
			  T,
			  U,
			  V,
			  W,
			  X,
			  Y,
			  Z,
			  Num0,
			  Num1,
			  Num2,
			  Num3,
			  Num4,
			  Num5,
			  Num6,
			  Num7,
			  Num8,
			  Num9,
			  Escape,
			  LControl,
			  LShift,
			  LAlt,
			  LSystem,
			  RControl,
			  RShift,
			  RAlt,
			  RSystem,
			  Menu,
			  LBracket,
			  RBracket,
			  SemiColon,
			  Comma,
			  Period,
			  Quote,
			  Slash,
			  BackSlash,
			  Tilde,
			  Equal,
			  Dash,
			  Space,
			  Return,
			  Back,
			  Tab,
			  PageUp,
			  PageDown,
			  End,
			  Home,
			  Insert,
			  Delete,
			  Add,
			  Subtract,
			  Multiply,
			  Divide,
			  Left,
			  Right,
			  Up,
			  Down,
			  Numpad0,
			  Numpad1,
			  Numpad2,
			  Numpad3,
			  Numpad4,
			  Numpad5,
			  Numpad6,
			  Numpad7,
			  Numpad8,
			  Numpad9,
			  F1,
			  F2,
			  F3,
			  F4,
			  F5,
			  F6,
			  F7,
			  F8,
			  F9,
			  F10,
			  F11,
			  F12,
			  F13,
			  F14,
			  F15,
			  Pause,
			  NumTeclas
		};

		/**
		 * @brief Constructor por defecto
		 * Pone las teclas de movimiento por defecto a WASD
		 */
		//Teclado();

		/**
		 * Destructor por defecto
		 */
		//~Teclado();

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		//Teclado(const Teclado& cop);

		/**
		 * Operador asignaci�n
		 * @param cop Origen de la copia
		 * @return Referencia al resultado de la copia
		 */
		//Teclado& operator=(const Teclado& cop);

		/**
		 * Indica si una tecla esta o no pulsada (para ello debemos haberla configurado antes)
		 * @param tecla Tecla que preguntamos (debe estar en el enum, para abstraernos de la SFML)
		 * @return TRUE si esta pulsada
		 */
		static bool isPulsada(Tecla tecla);

	private:
		/**
		 * Map que asocia las acciones a teclas
		 */
		//map<Tecla, sf::Keyboard::Key> c_map_teclas;


		/**
		 * Funcion auxiliar que copia un objeto en otro
		 * @param cop Objeto que se copia
		 */
		//void copiarDesde(const Teclado& cop);

	};

} /* namespace candy */
#endif /* EVENTOTECLADO_H_ */
