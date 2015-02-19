/*
 * Camera.h
 *
 *  Created on: 19/11/2011
 *      Author: kaseyo
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "OpenGL.h"
#include "CandyMath.h"

#include "GNode.h"

namespace candy {

/**
 * \addtogroup CandyGraphics
 * @{
 */
	/**
	 * @class Camera
	 * @brief Hereda de GNode y representa una camara en el arbol.
	 */
	class Camera : public GNode {
	public:
		/**
		 * Constructor a partir de los parametros
		 * @param param1 3D: Plano cercano de recortado -- 2D: Coordenada left de la proyeccion
		 * @param param2 3D: Plano lejano de recortado -- 2D: Coordenada right de la proyeccion
		 * @param param3 3D: Ratio del aspecto -- 2D: Coordenada top de la proyeccion
		 * @param param4 3D: Angulo de vision (fov) -- 2D: Coordenada bottom de la proyeccion
		 * @param tresde Indica si queremos que la camara sea 3D (proyeccion perspectiva), o 2D (proyeccion paralela)
		 */
		Camera(float param1, float param2, float param3, float param4, bool tresde);

		/**
		 * Destructor por defecto
		 */
		~Camera();

		/**
		 * Constructor de copia
		 * @param cop Copia
		 */
		Camera(const Camera& cop);

		/**
		 * Operador asignación de la camara.
		 * @param cop Origen de la copia
		 * @return Devuelve una referencia al resultado de la copia
		 */
		Camera& operator=(const Camera& cop);

		/**
		 * Metodo heredado de GNode
		 */
		void Render(bool seleccion);

		/**
		 * Settea los parametros de la camara 3D, con proyeccion perspectiva
		 * @param near Plano cercano de recortado
		 * @param far Plano lejano de recortado
		 * @param aspectRatio Ratio del aspecto
		 * @param fov Angulo de vision
		 */
		void setParameters3D(float near, float far, float aspectRatio, float fov);

		/**
		 * Settea los parametros de la camara 2D, con proyeccion paralela
		 * @param left Coordenada izquierda
		 * @param right Coordenada derecha
		 * @param top Coordenada top
		 * @param bottom Coordenada bottom
		 */
		void setParameters2D(float left, float right, float top, float bottom);


		/**
		* Seleccion el objeto que aparecen las coordenadas x,y de la pantalla
		* @param x, coordenada x
		* @param y, coordenada y
		* @return id del objeto seleccionado
		*/
		int seleccion(int x,int y);

	private:
		/**
		 * Copia un objeto en otro
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const Camera& cop);

		/**
		 * Angulo con el que mira la camara (fov - PI/2.5) --- SOLO 3D
		 */
		float c_fov;

		/**
		 * Distancia del plano de recortado lejano (2000) --- SOLO 3D
		 */
		float c_far;

		/**
		 * Distancia del plano de recortado cercano (1) --- SOLO 3D
		 */
		float c_near;

		/**
		 * Ratio del aspecto (ancho/alto de la camara - 4/3) --- SOLO 3D
		 */
		float c_aspectRatio;

		/**
		 * Coordenada left de la proyeccion. --- SOLO 2D
		 */
		float c_left;

		/**
		 * Coordenada right de la proyeccion. --- SOLO 2D
		 */
		float c_right;

		/**
		 * Coordenada top de la proyeccion. --- SOLO 2D
		 */
		float c_top;

		/**
		 * Coordenada bottom de la proyeccion. --- SOLO 2D
		 */
		float c_bottom;

		/**
		 * Booleano que indica si estamos usando una camara 2D o 3D.
		 * TRUE indica que estamos usando 3D, y por tanto usamos una proyeccion perspectiva.
		 * FALSE indica que estamos usando 2D, y por tanto usamos una proyeccion paralela (con far y near, 1 y -1).
		 */
		bool c_3D;

	};

} /* namespace candy */
#endif /* CAMERA_H_ */
