/*
 * PolygonFactory.cpp
 *
 *  Created on: 17/03/2012
 *      Author: kaseyo
 */

#include "PolygonFactory.h"

namespace candy {

Polygon
PolygonFactory::Cuadrado(Vector2 centro, float ancho, float alto){
	Contour contorno;

	float c_x = centro.getX();
	float c_y = centro.getY();

	float h_ancho = ancho / 2.0;
	float h_alto = alto / 2.0;

	contorno.push_back(Vector2(c_x + h_ancho, c_y + h_alto));
	contorno.push_back(Vector2(c_x - h_ancho, c_y + h_alto));
	contorno.push_back(Vector2(c_x - h_ancho, c_y - h_alto));
	contorno.push_back(Vector2(c_x + h_ancho, c_y - h_alto));

	return Polygon(contorno);
}

Polygon
PolygonFactory::Circulo(Vector2 centro, float radio){
	Contour contorno;

	float c_x = centro.getX();
	float c_y = centro.getY();

	float segmentos=10;
	float incremento=2*M_PI/10.0;
	float angulo = -incremento/2.0; //Para que dibuje los poligonos horizontales y no salgan doblados

	for(int i=0; i<segmentos; i++){
		float x = radio*cos(angulo) - c_x;
		float y = radio*sin(angulo) + c_y;
		contorno.push_back(Vector2(x + c_y,y + c_x));
		angulo+=incremento;
	}

	return Polygon(contorno);
}

Polygon
PolygonFactory::Poligono(Vector2 centro, float radio, int num_lados){
	Contour contorno;

	float c_x = centro.getX();
	float c_y = centro.getY();

	float segmentos=num_lados;
	float incremento=2*M_PI/num_lados;
	float angulo = -incremento / 2.0; //Para que dibuje los poligonos horizontales y no salgan doblados

	for(int i=0; i<segmentos; i++){
		float x = radio*cos(angulo) - c_x;
		float y = radio*sin(angulo) + c_y;
		contorno.push_back(Vector2(x + c_y,y + c_x));
		angulo+=incremento;
	}

	return Polygon(contorno);
}

} /* namespace candy */
