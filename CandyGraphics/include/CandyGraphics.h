/*
 * CandyGraphics.h
 *
 *  Created on: 17/11/2011
 *      Author: kaseyo
 */

#ifndef CANDYGRAPHICS_H_
#define CANDYGRAPHICS_H_


//Arbol de renderizado
#include "Camera.h"
#include "Director.h"
#include "Transformation.h"
#include "AnimatedTransformation.h"
#include "Light.h"
#include "Shape.h"
#include "Model.h"
#include "Text.h"
#include "Scene.h"
#include "Line.h"
#include "Box.h"
#include "Plane.h"
#include "Particles.h"


#include "GTree.h"
#include "GNode.h"

#include "guiButton.h"
#include "guiGBox.h"
#include "guiRButton.h"
#include "guiSlide.h"


//Ventana
#include "Ventana.h"
#include "Console.h"
#include "Raton.h"
#include "Teclado.h"
#include "Timer.h"

//Otros
#include "Color.h"
#include "CandyMath.h"
#include "GestorRecursos.h"
#include "OpenGL.h"
#include "ModelAnimation.h"

//GUI
#include "guiButton.h"
#include "guiGBox.h"
#include "guiSlide.h"

namespace candy {
/**
 * \addtogroup CandyGraphics
 * Motor Grafico en 3D.
 * @{
 */
	/**
	 * @class CandyGraphics
	 * @brief Clase principal del motor e interfaz con el usuario.
	 * Representa al motor grafico.
	 */
	class CandyGraphics {
	public:
		/**
		 * Constructor por defecto
		 */
		CandyGraphics();

		/**
		 * Destructor por defecto
		 */
		~CandyGraphics();

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		CandyGraphics(const CandyGraphics& cop);

		/**
		 * Operador asignaci�n
		 * @param cop Origen de la copia
		 * @return Resultado de la asignaci�n
		 */
		CandyGraphics& operator=(const CandyGraphics& cop);

		/**
		 * Metodo Render, que llama al render de escena
		 */
		void Render();

		/**
		 * Devuelve el puntero a escena
		 * @return
		 */
		Scene* getScenePtr();

		/**
		 * Inicializa algunos parametros de OpenGL.
		 */
		void InitOpenGL();

		/**
		 * Setter del valor de limpieza del color
		 * @param c Color
		 */
		void setClearColor(const Color& c);

		/**
		 * Seleccion el objeto que aparecen las coordenadas x,y de la pantalla
		 * @param x, coordenada x
		 * @param y, coordenada y
		 * @return id del objeto seleccionado
		 */
		int seleccion(int x,int y);

	private:
		/**
		 * Funcion auxiliar que copia un objeto en otro.
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const CandyGraphics& cop);

		/**
		 * Puntero a escena.
		 */
		Scene* c_escena;

	};

} /* namespace candy */
#endif /* CANDYGRAPHICS_H_ */
