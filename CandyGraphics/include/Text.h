/*
 * Text.h
 *
 *  Created on: 12/02/2012
 *      Author: carrillo
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "GNode.h"
#include "Color.h"
#include "OpenGL.h"
#include "FTGL/ftgl.h"
#include "GestorRecursos.h"
#include "MatrixStack.h"
#include "Timer.h"
#include "Transformation.h"
namespace candy {

class Text: public candy::GNode {
public:

	Text();
	Text(const Text &o);
	virtual ~Text();
	void Render(bool seleccion);
	void setTamanyo(int tam);
	bool setFont(int idFuente);
	bool setFont(FTGLPixmapFont* fuente);

	void setColor(const Color& color);

	string getTexto();
	void setTexto(string t);

	int getTamanyo();

	/**
	 * Devuelve un valor aproximado del tamaño posible de la cadena
	 * @return
	 */
	float getWidth();
	void setFontAnimated(int min,int max, int milisegundos);
	void desactiveAnimated();
	void setTransformation(Transformation* trans);
private:

	Transformation* transformacion;

	bool animationActivated;
	int animationMin;
	int animationMax;
	int animationDuracion;
	int	animationLastTime;
	int dir;

	void copiarDesde(const Text &o);
	FTGLPixmapFont* fuente;
	int tamanyo;
	string texto;
	Transformation* pos;
	//MatrixStack* pilaMatrices;
	Color color;
};

} /* namespace candy */
#endif /* TEXT_H_ */
