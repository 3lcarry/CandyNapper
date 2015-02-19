/*
 * Light.h
 *
 *  Created on: 08/02/2012
 *      Author: kaseyo
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "CandyMath.h"
#include "GNode.h"
#include "OpenGL.h"

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */
	/**
	 * @class Light
	 * @brief Hereda de GNode y representa una luz en el arbol. Por encima, en candygraphics, la funcion addlights
	 * o su equivalente controlara que no se pase de GL_MAX_LIGHTS
	 */
	class Light : public GNode {
	public:
		/**
		 * Constructor por defecto de Light
		 */
		Light(Vector3 posicion, Vector3 ambiente, Vector3 difusa, Vector3 especular, int numLuz);

		/**
		 * Destructor por defecto de Light
		 */
		~Light();

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		Light(const Light& cop);

		/**
		 * Operador asignacion
		 * @param cop Origen de la copia
		 * @return Resultado de la copia
		 */
		Light& operator=(const Light& cop);

		/**
		 * Setter de la posicion de la luz
		 * @param posicion Posicion deseada
		 */
		void setPosition(Vector3 posicion);

		/**
		 * Setter de la intensidad de la luz ambiente
		 * @param ambiente Luz ambiente
		 */
		void setAmbient(Vector3 ambiente);

		/**
		 * Setter de la intensidad de la luz difusa
		 * @param difusa Luz difusa
		 */
		void setDiffuse(Vector3 difusa);

		/**
		 * Setter de la intensidad de la luz especular
		 * @param especular Luz especular
		 */
		void setSpecular(Vector3 especular);

		/**
		 * Desactiva esta luz
		 */
		void disableLight();

		/**
		 * Activa esta luz
		 */
		void enableLight();

		/**
		 * Funcion que hereda e implementa de GNode
		 */
		void Render(bool seleccion);

		/**
		 * Maximo numero de luces en escena
		 */
		static const int MAX_LIGHTS;

	private:

		/**
		 * Funcion auxiliar que copia una luz en otra.
		 * @param cop Origen de la copia.
		 */
		void copiarDesde(const Light& cop);

		/**
		 * Posicion de la camara
		 */
		Vector3 c_posicion;

		/**
		 * Intensidad de la luz ambiente (para cada color)
		 */
		Vector3 c_ambiente;

		/**
		 * Intensidad de la luz difusa (para cada color)
		 */
		Vector3 c_difusa;

		/**
		 * Intensidad de la luz especular (para cada color)
		 */
		Vector3 c_especular;

		/**
		 * Entero que almacena el ID de luz que tiene
		 */
		int c_numLuz;

		/**
		 * Variable estatica privada que guarda los valores del enum para cada luz
		 */
		static const int c_enumLuces[7];
	};

} /* namespace candy */
#endif /* LIGHT_H_ */
