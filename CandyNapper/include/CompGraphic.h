/*
 * GraphicComponent.h
 *
 *  Created on: 15/02/2012
 *      Author: kaseyo
 */

#ifndef GRAPHICCOMPONENT_H_
#define GRAPHICCOMPONENT_H_

#include "IComponent.h"
#include "CandyGraphics.h"
#include "GameEntity.h"
#include "Timer.h"

namespace candy {

	class GEDynamic;

	/**
	 * @class GraphicComponent
	 * @brief Componente grafico para las entidades
	 * Componente, que hereda de IComponent, encargado de la parte grafica
	 */
	class CompGraphic : public IComponent{
	public:
		/**
		 * Constructor por defecto
		 */
		CompGraphic(GameEntity* entidad);

		/**
		 * Destructor por defecto
		 */
		~CompGraphic();

		/**
		 * Metodo heredado de IComponent
		 * @param entidad Entidad que "llama" al metodo, sobre los atributos de la cual trabajaremos
		 */
		void Update(GameEntity* entidad);

	private:

		/**
		 * Actualiza los parametros de la entidad dinamica
		 * @param entidad Entidad dinamica
		 */
		void actualizar(GEDynamic* entidad);

		/**
		 * Puntero a la transformacion del modelo
		 */
		Transformation* c_transformacion;

		/**
		 * Puntero al modelo
		 */
		Model* c_modelo;

		/**
		 * Modelo estandar "Quieto"
		 */
		int _modelDefault;
		/**
		 * Vector Modelos Movimiento
		 */
		vector<int> _modelMovement;
		/**
		 * MovimientoActual
		 */
		int _actualMovement;

		/**
		 * Ultimo cambio de la animacion
		 */
		unsigned int _lastTime;

		/**
		 * Modelo en uso actualmente
		 */
		int _modelUse;
		/**
		 * Textura en uso actualmente
		 */
		int _textureUse;
		/**
		 * Vector de texturas ordenadas de + vida a -
		 */
		vector<int> _texturas;

		ModelAnimation _animacion;
		ModelAnimation _animacionAtaque;
		int _texturaModel;

		bool _atacando;
		int _ultimoAtaque;
	};

} /* namespace candy */
#endif /* GRAPHICCOMPONENT_H_ */
