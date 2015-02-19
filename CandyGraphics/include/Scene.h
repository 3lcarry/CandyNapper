/*
 * Scene.h
 *
 *  Created on: 09/02/2012
 *      Author: kaseyo
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "GNode.h"
#include "MatrixStack.h"
#include "OpenGL.h"

using namespace std;

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */
	/**
	 * @class Scene
	 * @brief Clase "dummy" que representa la escena.
	 * Es el "manejador" de la escena, la manera de crearlas. Se encarga de renderizar toda la escena,
	 * ademas de controlar el ciclo de vida de la pila de matrices
	 */
	class Scene : public GNode {
	public:
		/**
		 * Constructor por defecto
		 */
		Scene();

		/**
		 * Destructor por defecto
		 */
		~Scene();

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		Scene(const Scene& cop);

		/**
		 * Operador asignacion
		 * @param cop Origen de la asignacion
		 * @return Referencia al resultado
		 */
		Scene& operator=(const Scene& cop);

		/**
		 * Encargado de renderizar toda la escena
		 */
		void Render(bool seleccion);

	private:

		/**
		 * Funcion auxiliar que copia un objeto en otro
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const Scene& cop);

		/**
		 * Limpia la escena, el contexto de OpenGL (de posible basura que haya quedado de antes)
		 */
		void loadIdentitys();

		/**
		 * Reimplementacion del metodo RenderHijos de GNode (para hacer un ClearScene() cada vez
		 * que hacemos un Rener()
		 */
		void RenderHijos(bool seleccion);

		/**
		 * Guarda un puntero a la instancia de la matrixstack. Asi podra destruirla al morir.
		 */
		MatrixStack* c_pila;
	};

} /* namespace candy */
#endif /* SCENE_H_ */
