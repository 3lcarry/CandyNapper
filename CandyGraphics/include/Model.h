/*
 * Model.h
 *
 *  Created on: 09/02/2012
 *      Author: carrillo
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "GNode.h"
#include "GestorRecursos.h"

namespace candy {

class Model: public candy::GNode {
public:
        
	/**
	 * Constructor por defecto de los Modelos, si no se especifica ningun modelo, no mostrara
	 * nada
	 */
	Model();

	/**
	 * Crea un modelo indicandole que id del gestor de recursos debe utilizar
	 * @param idModel id del gestor de recursos que debe utilizar
	 * @param textura textura para el modelo, -1 sin textura
	 */
	Model(int idModel,int textura = -1);

	/**
	 * Constructor de copia
	 * @param cop Origen de la copia
	 */
	Model(const Model& cop);

	/**
	 * Elimina el modelo
	 */
	virtual ~Model();

	/**
	 * Operador =, crea dos modelos identicos
	 * @param o origen de la copia
	 * @return Resultado
	 */
	Model& operator=(const Model& o);

	/**
	 * Renderiza, si el id del modelo no existe o es incorrecto
	 * no dibuja nada
	 */
	void Render(bool seleccion);

	/**
	 * Introduce el modelo a renderizar
	 * @param id
	 */
	void setIdModel(int id);

	/**
	 * Obtiene que modelo esta pintando
	 * @return id
	 */
	int getIdModel();

	/**
	 * Settea el shader
	 * @param shader Indice del shader
	 */
	void setShader(int shader);

	/**
	 * Coloca el color base al modelo
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	inline void setColor(float r, float g, float b, float a) {color[0]=r;color[1] = g;color[2]=b;color[3]=a;}

	/**
	 * @return Vector de colores incluye alpha
	 */
	inline float* getColor(){return color;}

	/**
	 * Indica la textura del modelo
	 * @param id textura del gestor de recursos
	 */
	inline void setTexture(int id){texture = id;}

	/**
	 * Devuelve la textura
	 * @return
	 */
	inline int getTexture(){return texture;}
private:
	/**
	 * Modelo a pintar del gestor de recursos
	 */
	int idModel;
	/**
	 * Color Base del Modelo
	 */
	float color[4];
	/**
	 * Textura, sin textura -1
	 */
	int texture;

	/**
	 * Indice del shader en el gestor de recursos
	 */
	int _shader;

	/**
	 * Funcion auxiliar que copia un modelo en otro
	 * @param cop Origen de la copia
	 */
	void copiarDesde(const Model& cop);
};

} /* namespace candy */
#endif /* MODEL_H_ */
