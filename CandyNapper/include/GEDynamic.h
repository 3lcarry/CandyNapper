/*
 * GameEntityDynamic.h
 *
 *  Created on: Nov 8, 2011
 *      Author: carrillo
 */

#ifndef GAMEENTITYDYNAMIC_H_
#define GAMEENTITYDYNAMIC_H_

#include "GameEntity.h"
#include "StateMachine.h"
#include "Attack.h"

namespace candy {
/**
 * \addtogroup CandyEngine
 * @{
 */

	/**
	 * @class GEDynamic
	 * @brief Entidad dinámica
	 * Hereda de la clase GameEntity. Representa a una entidad dinámica, es decir,
	 * que a lo largo del transcurso del juego se moverá (p. ej: nuestro player, o un enemigo)
	 */
	class GEDynamic: public GameEntity {
	public:

		/**
		 * Destructor por defecto
		 */
		virtual ~GEDynamic();

		/**
		 * Sette la posicion pasandole directamente un Vector3
		 * @param posicion Posicion de la entidad
		 */
		void setPosicion(Vector3 posicion);

		/**
		 * Indica si la entidad esta modificada.
		 * @return True si se ha modificado.
		 */
		bool isModificado();

		/**
		 * Setter del flag modificado.
		 * @param mod 'true' o 'false'.
		 */
		void setModificado(bool mod);

		/**
		 * Setter del angulo de vision de la entidad
		 * @param angulo Angulo de vision
		 */
		void setVisionX(float angulo);

		/**
		 * Setter del angulo de vision de la entidad
		 * @param angulo Angulo de vision
		 */
		void setVisionY(float angulo);

		/**
		 * Setter del angulo de movimiento
		 * @param angulo Angulo de movimiento
		 */
		void setAnguloMovimiento(float angulo);

		/**
		 * Setter de la velocidad
		 * @param velocidad Velocidad deseada
		 */
		void setVelocidad(float velocidad);

		/**
		 * Setter de la Vida restante
		 * @param vida restante
		 */
		void setVidaRestante(int vida);

		/**
		 * Setter del ataque
		 * @param objeto attack
		 */
		void setAttack(Attack *a);

		/**
		 * Incrementa la vida en x
		 * @param x lo que se aumenta de vida
		 */
		void incVida(int x = 1);

		/**
		 * Getter del angulo de vision
		 * @return Angulo de vision de la entidad (hacia donde mira)
		 */
		float getVisionX();

		/**
		 * Getter del angulo de vision
		 * @return Angulo de vision de la entidad (hacia donde mira)
		 */
		float getVisionY();

		/**
		 * Getter de la velocidad
		 * @return Velocidad de la entidad
		 */
		float getVelocidad();

		/**
		 * Getter del angulo de movimiento
		 * @return Angulo de movimiento de la entidad (hacia donde se mueve)
		 */
		float getAnguloMovimiento();

		/**
		 * Funcion encargada de que la entidad reciba un ataque
		 * @param attack Fuerza del ataque
		 */
		void RecibirAtaque(float attack);

		/**
		 * Indica si una entidad dinamica esta o no muerta (y por tanto el em tiene q borrarla)
		 * @return TRUE si esta muerta
		 */
		bool isMuerto();

		/**
		 * Devuelve la vida total
		 * @return Devuelve la vida total
		 */
		int getVidaTotal();

		/**
		 * Devuelve la voida restante
		 * @return Vida restante
		 */
		int getVidaRestante();

		/**
		 * Devuelve el radio de la entidad para la fisica
		 * @return
		 */
		int getRadio();

		/**
		 * Devuelve el ataque de la entidad
		 * @return ataque
		 */
		Attack* getAttack();

		/**
		 * Velocidad normal para mover al player
		 */
		static const float VelocidadNormal;

		/**
		 * Modificador de la velocidad
		 * @param fraccion que queremos que incremente o decremente
		 */
		void setModificadorVelocidad(float fraccion);

	protected:
		/**
		 * Factor modificador de la velocidad
		 */
		float _modificadorVelocidad;
		/**
		 * Constructor a partir de un ID
		 * @param id ID del objeto
		 * @param posicion Posicion de la entidad
		 * @param tipo Tipo de entidad dinamica (puede ser player o enemy).
		 */
		GEDynamic(TipoEntidad tipo, int id, Vector3 posicion);

		/**
		 * Constructor de copia
		 * @param cop Copia origen
		 */
		GEDynamic(const GEDynamic &cop);

		/**
		 * Operador asignacion
		 * @param cop Origen de la copia
		 * @return Devuelve una referencia a nuestro objeto
		 */
		virtual GEDynamic& operator=(const GEDynamic &cop);

		/**
		 * Funcion auxiliar que copia un objeto en otro.
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const GEDynamic &cop);

		/**
		 * Velocidad actual de la entidad
		 */
		float c_velocidad;

		/**
		 * Angulo de "movimiento" de la entidad (la direccion en la que se mueve)
		 */
		float c_anguloMovimiento;

		/**
		 * Angulo de "vision" de la entidad (hacia donde esta mirando) en el ejeX
		 */
		float c_visionX;

		/**
		 * Angulo de "vision" de la entidad (hacia donde esta mirando) en el ejeY
		 */
		float c_visionY;

		/**
		 * Indica si la entidad ha visto modificada su posicion (Dirty o Modify bit)
		 */
		bool c_modificado;

		/**
		 * Vida de la entidad
		 */
		int _vidaRestante;

		/**
		 * Vida total de la entidad
		 */
		int _vidaTotal;

		/**
		 * Indica si la entidad ha muerto
		 */
		bool _muerto;

		/**
		 * Radio de la entidad dinamica para la fisica
		 */
		int _radio;

		/**
		 * Ataque de la entidad
		 */
		Attack* _ataque;
	};

} /* namespace candy */
#endif /* GAMEENTITYDYNAMIC_H_ */
