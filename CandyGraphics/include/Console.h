/*
 * Console.h
 *
 *  Created on: 08/02/2012
 *      Author: kaseyo
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>
#include <string>
#include <iterator>
#include <cstdlib>
#include <vector>

#include "GNode.h"
#include "Transformation.h"
#include "Text.h"
#include "Shape.h"
#include "GestorRecursos.h"
using namespace std;

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */

	/**
	 * @class Console
	 * @brief Consola de comandos asociada a la ventana
	 * Representa una consola (asociada a una ventana), en la que al pulsar una determinada tecla, nos dejara introducir comandos
	 * (que nosotros tendremos que encargarnos de leer en su momento e interpretar).
	 */
	class Console {
	public:
		/**
		 * Constructor por defecto
		 */
		Console();

		/**
		 * Destructor por defecto
		 */
		~Console();

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		Console(const Console& cop);

		/**
		 * Operador asignacion
		 * @param cop Origen de la copia
		 * @return Resultado de la copia
		 */
		Console& operator=(const Console& cop);

		/**
		 * Actualiza el estado de la consola, segun el cin.
		 */
		void AddChar(char caracter);

		/**
		 * Elimina el ultimo caracter
		 */
		void RmChar();

		/**
		 * Abre la consola.
		 */
		void ShowConsole();

		/**
		 * Guarda la consola
		 */
		void HideConsole();

		/**
		 * Metodo que indica si el comando esta completo o no (se ha introducido un salto de linea)
		 * @return TRUE si el comando esta completo
		 */
		bool IsComplete();

		/**
		 * Devuelve el comando (en teoria completado)
		 * @return Comando hasta el momento
		 */
		string GetCommand();

		/**
		 * Indica si la consola esta activa/inactiva
		 * @return TRUE si activa
		 */
		bool IsActive();

		/**
		 * Da por acabado el comando introducido
		 */
		void CommandCompleted();

		/**
		 * Devuelve el comando troceado por espacios
		 * @return Vector de strings con el comando troceado
		 */
		vector<string> GetCommandSplitted();

		/**
		 * Settea el nodo en el que se "dibujara" la consola
		 * @param nodo
		 */
		void setGNode(GNode* nodo);

	private:
		/**
		 * Funcion auxiliar que copia un objeto en otro
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const Console& cop);

		/**
		 * Muestra el prompt al usuario, preparado para leer algo
		 */
		void prompt();

		/**
		 * Limpia la terminal (deberia funcionar en cualquier plataforma)
		 */
		void clearConsole();

		/**
		 * Limpia el buffer de entrada del sistema
		 */
		void clearInput();

		/**
		 * Comando introducido hasta el momento (cuando metemos un \/n se "marca" para borrar).
		 * Se vacia cuando leemos el comando introducido o cuando vamos a introducir un nuevo comando.
		 */
		string c_comando;

		/**
		 * Variable que guarda si el comando esta o no completo (se ha introducido \/n).
		 * Se pone a TRUE cuando llamamos a CommandCompleted (que lo llama la ventana cuando detecta que se pulsa enter.
		 * Se pone a FALSE en dos casos. Cuando llamamos a AddChar (estamos introd un nuevo comando) y cuando hacemos un
		 * GetCommand (para recogerlo una sola vez). Por tanto, es deber del usuario el recoger y guardarse el comando si le
		 * interesa.
		 */
		bool c_completo;

		/**
		 * Indica si la consola esta actualmente activa o inactiva
		 */
		bool c_activa;

		/**
		 * Nodo a partir del que pinta la consola
		 */
		GNode* c_GNode;

		/**
		 * Nodo texto dentro de la consola
		 */
		Text* c_nodoTexto;

		/**
		 * Caja sobre la que pintamos la consola
		 */
		Shape* c_nodoCaja;
	};

} /* namespace candy */
#endif /* CONSOLE_H_ */
