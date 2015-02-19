/*
 * World3D.h
 *
 *  Created on: 01/03/2012
 *      Author: kaseyo
 */

#ifndef WORLD3D_H_
#define WORLD3D_H_

#include "CandyGraphics.h"

namespace candy {
/**
 * \addtogroup Graphics
 * @brief Modulo encargado de la gestion de la parte grafica.
 * @{
 */

	/**
	 * @class World3D
	 * Parte de la fachada del motor grafico. Representa al escenario 3D
	 */
	class World3D {
	public:
		/**
		 * Constructor por defecto
		 * @param ancho Ancho del mundo (hasta donde llega en X)
		 * @param profundo Profundidad del mundo (hasta donde llega en Z)
		 */
		World3D(Scene* escena, Ventana* v);

		/**
		 * Destructor por defecto
		 */
		~World3D();

		/**
		 * Resizea la camara 3D
		 * @param ancho Nuevo ancho
		 * @param alto Nuevo alto
		 */
		void Resize(float ancho, float alto);

		/**
		 * Obtiene la camara 3D
		 * @return Puntero a la camara 3D
		 */
		Camera* getCamera3D();

		/**
		 * Devuelve la transformacion del escenario 3D
		 * @return Transformacion de la que cuelgan todas las entidades 3D menos el player
		 */
		Transformation* getScene3D();

		/**
		 * Devuelve la transformacion encargada de la camara
		 * @return Transformacion encargada de la camara
		 */
		Director* getDirector();

		/**
		 * Devuelve la transformacion del cielo
		 * @return Transformation del cielo
		 */
		Transformation* getSky();

	private:
		/**
		 * Transformacion de la escena
		 */
		Transformation* _escena;

		/**
		 * Puntero a camara 3D
		 */
		Camera* _cam3D;

		/**
		 * Puntero al director que dirige la camara
		 */
		Director* _director;

		/**
		 * Puntero a la transformacion del sky
		 */
		Transformation* _sky;
	};

} /* namespace candy */
#endif /* WORLD3D_H_ */
