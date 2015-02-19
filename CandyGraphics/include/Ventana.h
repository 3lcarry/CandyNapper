/*
 * InOut.h
 *
 *  Created on: 04/11/2011
 *      Author: kaseyo
 */

#ifndef VENTANA_H_
#define VENTANA_H_

#include "Console.h"

#include <string>
#include <vector>
#include "SFML/Window.hpp"
using namespace std;

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */

	/**
	 * @class Ventana
	 * @brief Ventana con un contexto de OpenGL
	 * Representa una ventana con un contexto de OpenGL. Esta clase tambi�n se encarga de los eventos propios
	 * de la ventana, como el cerrar o el resize. Hemos intentado hacerla lo mas independiente posible. Podriamos decir
	 * que es una ventana "autocontenida". Adem�s, lleva asociada una consola.
	 */
	class Ventana {
	public:
		friend class Raton;


		/**
		 * @brief Constructor por defecto
		 * Constructor básico sin parametros de una ventana de tama�o maximo
		 */
		Ventana(string titulo = NombrePorDefecto);

		/**
		 * Constructor para un tama�o especifico
		 * @param ancho Ancho de la ventana
		 * @param alto Alto de la ventana
		 */
		Ventana(float ancho, float alto, string titulo = "Mi Ventana");

		/**
		 * @brief Destructor
		 * Destructor de nuestra clase
		 */
		~Ventana();

		/**
		 * @brief Constructor de copia
		 * Constructor de copia de la clase
		 * @param cop Objeto del que copìamos
		 */
		Ventana(const Ventana& cop);

		/**
		 * @brief Operador asignación
		 * Operador asignacion de nuestra clase
		 * @param cop Objeto del que copiamos
		 * @return Referencia al resultado de la copia
		 */
		Ventana& operator=(const Ventana& cop);

		/**
		 * @brief Pone una ventana en modo "Pantalla completa"
		 * Permite que una ventana se muestre en pantalla completa con el mejor modo de video posible
		 */
		void switchFullscreen();

		/**
		 * @brief Actualiza todos los eventos
		 * Actualiza los eventos (tanto relativos a la ventana como al raton y teclado) y envia una señal
		 * cuando ha sucedido alguno
		 */
		void Update();

		/**
		 * Devuelve el framerate actual
		 */
		float getFramesPerSecond();

		/**
		 * Devuelve TRUE si se quiere cerrar la ventana.
		 * Y pone el flag a FALSE
		 * @return TRUE si se quiere cerrar la ventana.
		 */
		bool isClosing();

		/**
		 * Devuelve TRUE si se quiere resize la ventana.
		 * Y pone el flag a FALSE
		 * @return TRUE si se quiere resize la ventana.
		 */
		bool isResizing();

		/**
		 * Devuelve TRUE si se quiere pausar el juego.
		 * @return TRUE si se quiere pausar.
		 */
//		bool isPause();

		/**
		 * Devuelve TRUE si se quiere fullscreen y pone el flag a false.
		 * Acto seguido, en el estado fullscreen habr� que llamar a setFullscreen(), que el solo
		 * intercambia entre fullscreen a normal y viceversa.
		 * @return TRUE si se quiere fullscreen.
		 */
		bool isFullScreen();

		/**
		 * Muestra la ventana
		 */
		void Display();

		/**
		 * Devuelve el ancho actual de la ventana
		 * @return Ancho
		 */
		float getWidth();

		/**
		 * Devuelve el alto actual de la ventana
		 * @return Alto
		 */
		float getHeight();

		/**
		 * Devuelve un puntero a la consola
		 * @return Puntero a la consola
		 */
		Console* getConsolePtr();

		/**
		 * Cambia de tama�o el Viewport actual
		 */
		void ResizeViewport();

		/**
		 * Muestra el mouse
		 * @param show TRUE si queremos mostrar el mouse. FALSE para esconderlo
		 */
		void ShowMouse(bool show);

		/**
		 * Indica si la ventana tiene el foco de atencion
		 * @return TRUE si es el centro de atencion
		 */
		bool isFocused();

	private:
		/**
		 * @brief Funcion de copia
		 * Funcion encargada de copiar un objeto sobre el nuestro. La llamaremos desde el constructor
		 * de copia y desde el operador asignación.
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const Ventana& cop);

		/**
		 * @brief Crea una ventana
		 * Crea una ventana con un contexto de OpenGL.
		 * @param width Ancho de la ventana
		 * @param height Alto de la ventana
		 */
		void crearVentana(float width, float height);

		/**
		 * @brief Crea una ventana
		 * Crea una ventana con un contexto de OpenGL y el tama�o maximo posible.
		 */
		void crearVentana();

		/**
		 * @brief Variable que representa a una ventana
		 */
		sf::Window c_window;

		/**
		 * Titulo de la ventana
		 */
		string c_titulo;

		/**
		 * Consola adicional a la ventana
		 */
		Console c_consola;

		/**
		 * Nombre de la ventana
		 */
		static const string NombrePorDefecto;

		/**
		 * Flag que indica si el usuario quiere cerrar la ventana
		 */
		bool c_close;

		/**
		 * Flag que indica si se quiere pausar el juego
		 */
		bool c_pause;

		/**
		 * Flag que indica si se quiere cambiar de tama�o la ventan
		 */
		bool c_resize;

		/**
		 * Flag que indica si queremos fullscreen (evento)
		 */
		bool c_fullscreen;

		/**
		 * Indica si la ventana tiene el focus o no
		 */
		bool c_focus;

		/**
		 * Flag que indica si estamos o no en fullscreen
		 */
		bool c_switchfullscreen;

		/**
		 * FPS actuales (tiempo pasado desde el ultimo frame)
		 */
		float c_fps;

		/**
		 * Reloj para medir los fps
		 */
		sf::Clock c_reloj;
	};

} /* namespace candy */
#endif /* VENTANA_H_ */
