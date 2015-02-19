/*
 * CompMinimap.h
 *
 *  Created on: 16/02/2012
 *      Author: kaseyo
 */

#ifndef COMPMINIMAP_H_
#define COMPMINIMAP_H_

#include "InterfazGraphics.h"
#include "CandyGraphics.h"
#include "IComponent.h"
#include "GameEntity.h"
#include "GEDynamic.h"

namespace candy {
	/**
	 * @class CompMinimap
	 * @brief Componente encargado de dibujar la entidad en el minimapa
	 * Componente, que hereda de IComponent, encargado de dibujar la entidad en el minimapa
	 */
	class CompMinimap : public IComponent {
	public:
		/**
		 * Constructor por defecto
		 */
		CompMinimap(GameEntity* entidad);

		/**
		 * Destructor por defecto
		 */
		~CompMinimap();

		/**
		 * Metodo encargado de actualizar la pos en el minimapa
		 * @param entidad Entidad que dibujamos
		 */
		void Update(GameEntity* entidad);

	private:
		/**
		 * Traduce de un Vector3 (pos_3D) a un Vector2
		 * @param pos_3d Posicion 3D de la entidad
		 * @return Vector2 con la posicion transformada
		 */
		Vector2 scene2minimap(Vector3 pos_3d);

		/**
		 * Transformacion para moverlos dentro del minimapa
		 */
		Transformation* c_transformacion;

		/**
		 * Poligono que les representa en el minimapa
		 */
		Shape* c_polygon;
	};

} /* namespace candy */
#endif /* COMPMINIMAP_H_ */
