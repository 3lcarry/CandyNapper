/*
 * CompGraphicPlayer.h
 *
 *  Created on: 20/02/2012
 *      Author: kaseyo
 */

#ifndef COMPGRAPHICPLAYER_H_
#define COMPGRAPHICPLAYER_H_

#include "InterfazGraphics.h"
#include "IComponent.h"
#include "Timer.h"


namespace candy {
	class Player;
	class GameEntity;

	/**
	 * @class CompGraphicPlayer
	 * @brief Componente grafico para las entidades (especial para el player)
	 * Componente, que hereda de IComponent, encargado de la parte grafica del player (que necesita un tratamiento especial)
	 */
	class CompGraphicPlayer : public IComponent{
	public:
		/**
		 * Constructor por defecto
		 * @param entidad Puntero a la entidad
		 */
		CompGraphicPlayer(GameEntity* entidad);

		/**
		 * Destructor por defecto
		 */
		~CompGraphicPlayer();

		/**
		 * Metodo Update heredado de GameEntity
		 * @param entidad Entidad que actualizamos
		 */
		void Update(GameEntity* entidad);

	private:

		/**
		 * Funcion auxiliar que llamamos tanto en el constructor como en el Update
		 * @param entidad
		 */
		void actualizar(Player* entidad);

		/**
		 * Puntero a la rotacion de la escena
		 */
		Transformation* c_tEscena;

		/**
		 * Transformacion del cielo
		 */
		Transformation* _tSky;

		/**
		 * Puntero a la transformacion del player
		 */
		Transformation* c_tplayer;

		/**
		 * Puntero al modelo del player
		 */
		Model* c_mplayer;

		Particles* particulas;

		/**
		 * Indica el ultimo director setteado (para cambiarlo solo cuando debamos)
		 * TRUE indica el modo apuntando
		 * FALSE indica el modo normal
		 */
		bool c_apuntandoSetted;

		/**
		 * Indica si esta ya setteado Hans (lo tomamos como referencia)
		 */
		bool c_hansSetted;

		/**
		 * Parametros del director del modo apuntando (Centro)
		 */
		static Vector3 c_apuntandoCentro;

		/**
		 * Parametros del director del modo apuntando (Referencia)
		 */
		static Vector3 c_apuntandoReferencia;

		/**
		 * Parametros del director del modo apuntando (Up)
		 */
		static Vector3 c_apuntandoUp;

		/**
		 * Parametros del director del modo normal (Centro)
		 */
		static Vector3 c_normalCentro;

		/**
		 * Parametros del director del modo normal (Referencia)
		 */
		static Vector3 c_normalReferencia;

		/**
		 * Parametros del director del modo normal (Up)
		 */
		static Vector3 c_normalUp;
		/**
		 * MovimientoActual
		 */
		int _actualMovement;
		/**
		 * Modelo estandar "Quieto"
		 */
		int _modelDefault;
		/**
		 * Vector Modelos Movimiento
		 */
		vector<int> _modelMovement;

		vector<int> _modelMovementTia;
		/**
		 * Vector de texturas ordenadas de + vida a -
		 */
		vector<int> _texturas;
		/**
		 * Ultimo cambio de la animacion
		 */
		unsigned int _lastTime;
		/**
		 * Modelo en uso actualmente
		 */
		int _modelUse;

		int _utlimoAtaque;

		bool _atacandoTio;
		bool _atacandoTia;
		/**
		 * Animacion Movimiento Tio
		 */
		ModelAnimation _movimientoTio;
		/**
		 * Animacion Ataque Tio
		 */
		ModelAnimation _ataqueTio;

		/**
		 * Animacion Movimiento Tia
		 */
		ModelAnimation _movimientoTia;

		ModelAnimation _ataqueTia;

		/**
		 * Modelo default tio
		 */
		int _modelTio;

		/**
		 * Modelo default tia
		 */
		int _modelTia;
	};

} /* namespace candy */
#endif /* COMPGRAPHICPLAYER_H_ */
