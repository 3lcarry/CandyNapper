/*
 * Polygon.h
 *
 *  Created on: 15/03/2012
 *      Author: kaseyo
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include "clipper.hpp"
#include "poly2tri/poly2tri.h"
#include "Vector2.h"
#include <vector>
#include <stdlib.h>
using namespace std;

namespace candy {

	typedef vector<candy::Vector2> Contour;


	/**
	 * @class Polygon
	 * Poligono geometrico en 2 dimensiones, que guarda una serie de puntos que lo componen. Ademas, permite su conversion a la libreria
	 * poly2tri (en un array de p2t::Point), y operaciones booleanas mediante la libreria GPC
	 */
	class Polygon {
	public:
		/**
		 * Operador salida para Polygon
		 * @param os Ostream
		 * @param pol Polygono que imprimimos
		 * @return Referencia del ostream
		 */
		friend ostream& operator<<(ostream& os, const Polygon& pol);

		/**
		 * Constructor por defecto
		 */
		Polygon();

		/**
		 * Constructor a partir de una serie de poligonos ya definidos
		 * @param puntos Array de poligonos
		 */
		Polygon(vector<Contour> poligonos);

		/**
		 * Constructor a partir de un unico poligono
		 * @param poligono Poligono
		 */
		Polygon(Contour poligono);

		/**
		 * Constructor a partir de un conjunto de poligonos de Clipper
		 * De momento solo tenemos en cuenta el primero
		 * @param polig
		 */
		Polygon(const ClipperLib::Polygons& polig);

		/**
		 * Destructor
		 */
		~Polygon();

		/**
		 * Constructor de copia del poligono
		 * @param pol Origen de la copia
		 */
		Polygon(const Polygon& pol);

		/**
		 * Operador asignacion
		 * @param pol Origen de la asignacion
		 * @return Resultado de la asignacion
		 */
		Polygon& operator=(const Polygon& pol);

		/**
		 * Une nuestro poligono con otro y devuelve el resultado
		 * @param pol Poligono con el que unimos
		 * @return Resultado de la union
		 */
		Polygon Union(const Polygon& pol) const;

		Polygon OuterUnion(const Polygon& pol) const;

		/**
		 * Intersecta nuestro poligono con otro y devuelve el resultado
		 * @param pol Poligono con el que intersectamos
		 * @return Resultado de la interseccion
		 */
		Polygon Interseccion(const Polygon& pol) const;

		Polygon OuterInterseccion(const Polygon& pol) const;

		/**
		 * Hace la diferencia entre nuestro poligono y otro
		 * @param pol Poligono que restamos
		 * @return Resultado de la diferencia
		 */
		Polygon Diferencia(const Polygon& pol) const;

		Polygon OuterDiferencia(const Polygon& pol) const;

		/**
		 * Hace la operacion XOR entre nuestro poligono y otro
		 * @param pol Poligono con el que hacemos la XOR
		 * @return Resultado de la XOR
		 */
		Polygon Xor(const Polygon& pol) const;

		Polygon OuterXor(const Polygon& pol) const;

		/**
		 * Indica si el poligono esta vacio
		 * @return TRUE si esta vacio
		 */
		bool isVacio() const;

		/**
		 * Anyade un vertice al poligono
		 * @param vertice Vertice que anyadimos
		 */
		void addVertex(Vector2 vertice, unsigned index = 0);

		/**
		 * Settea los arrays del vertice
		 * @param vertices Vertices que setteamos
		 */
		void setContour(Contour, unsigned index = 0);

		/**
		 * Devuelve el vertexarray
		 * @param index Indice de cual queremos
		 */
		Contour getContour(unsigned index = 0);

		/**
		 * Settea todos los poligonos
		 * @param poligonos Array de poligonos
		 */
		void setContours(vector<Contour> poligonos);

		/**
		 * Permite obtener el array de vertices
		 * @return Devuelve el array de vertices
		 */
		vector<Contour> getContours();

		/**
		 * Expande el poligono la distancia indicada
		 * @param expansion Unidades que expandimos
		 * @return Poligono expandido
		 */
		Polygon Expandir(float expansion) const;

		/**
		 * "Wrapper" para obtener el polygono segun la ClipperLib. Si hay alguno definido, devuelve ese.
		 * Si no, devuelve uno nuevo recien creado
		 * @return Array de poligonos de la ClipperLib
		 */
		ClipperLib::Polygons getClipperPolygons() const;

		/**
		 * "Wrapper" para obtener el polygono segun la poly2tri
		 * @return Array de puntos de la poly2tri
		 */
		vector<vector<p2t::Point*> > getPoly2TriPolygons() const;

		/**
		 * Devuelve el numero de contornos que hay
		 * @return Numero de contornos que tiene el poligono
		 */
		int getContoursNumber() const;

		/**
		 * Devuelve el numero de vertices del poligono
		 * @return Numero de vertices
		 */
		int getNumVertices() const;

	private:
		/**
		 * Puntos que componen el poligono
		 */
		vector<Contour> _contornos;

		/**
		 * Representacion del poligono en formato Clipper
		 */
		ClipperLib::Polygons* _clipperPolygons;

		/**
		 * Copia desde un pol al nuestro
		 * @param pol Origen de la copia
		 */
		void copiarDesde(const Polygon& pol);

		/**
		 * Libera la mem
		 */
		void freeMem();
	};

} /* namespace candy */
#endif /* POLYGON_H_ */
