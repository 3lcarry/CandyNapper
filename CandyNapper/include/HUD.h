/*
 * HUD.h
 *
 *  Created on: 01/03/2012
 *      Author: kaseyo
 */

#ifndef HUD_H_
#define HUD_H_

#include "CandyGraphics.h"

namespace candy {
/**
 * \addtogroup Graphics
 * @brief Modulo encargado de la gestion de la parte grafica.
 * @{
 */

	/**
	 * @class HUD
	 * Parte de la fachada del motor grafico. Representa al HUD que se imprime por pantalla
	 */
	class HUD {
	public:
		/**
		 * Constructor pasandole un ancho y un alto
		 */
		HUD(Scene* escena, Ventana* v);

		/**
		 * Destructor por defecto
		 */
		~HUD();

		/**
		 * Getter de la camara del HUD
		 * @return Devuelve la camara del HUD
		 */
		Camera* getHUDCamera();

		/**
		 * Devuelve la transformacion del minimapa
		 * @return Transformacion del minimapa
		 */
		Transformation* getMinimap();

		/**
		 * Se resizea el HUD a los parametros pasados
		 * @param ancho Ancho del HUD
		 * @param alto Alto del HUD
		 */
		void Resize(float ancho, float alto);

		//DEBUG
		Text* getText1();
		Text* getText2();
		Transformation* getBox1();
		Text* getMensajeCentral();

	private:
		/**
		 * Camara 2D del HUD
		 */
		Camera* _cam2D;

		/**
		 * Puntero a la transformacion del minimapa del HUD
		 */
		Transformation* _minimapa;

		/**
		 * Puntero a la transformacion de la mirilla
		 */
		Transformation* _mirilla;

		Text* _mensajeCentral;


		//DEBUG
		Text* _text1;

		Text* _text2;


		Transformation* _box1;
	};

} /* namespace candy */
#endif /* HUD_H_ */
