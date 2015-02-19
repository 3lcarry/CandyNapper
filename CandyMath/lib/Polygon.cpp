/*
 * Polygon.cpp
 *
 *  Created on: 15/03/2012
 *      Author: kaseyo
 */

#include "Polygon.h"

namespace candy {

ostream &
operator <<(ostream & os, const Polygon & pol){
	os << "{ ";
	for(unsigned i = 0; i < pol._contornos.size(); i++){
		if(i != 0){
			os << endl;
		}

		os << "[ ";

		for(unsigned j = 0; j < pol._contornos[i].size(); j++){
			if(j != 0){
				os << " , ";
			}

			os << pol._contornos[i][j];
		}

		os << "] ";
	}
	os << " }";

	return os;
}

Polygon::Polygon() {
	//_gpcPoligon = getGPCPolygon();
	//_clipperPolygon = getClipperPolygon();
	_clipperPolygons = NULL;
}

Polygon::Polygon(Contour puntos){
	setContour(puntos, 0);
	_clipperPolygons = NULL;
}

Polygon::Polygon(const ClipperLib::Polygons& polygons){
	for(unsigned i = 0; i < polygons.size(); i++){
		Contour polygono;
		for(unsigned j = 0; j < polygons[i].size(); j++){
			polygono.push_back(Vector2(polygons[i][j].X, polygons[i][j].Y));
		}
		_contornos.push_back(polygono);
	}

	_clipperPolygons = new ClipperLib::Polygons;

	for(unsigned i = 0; i < polygons.size(); i++){
		ClipperLib::Polygon nuevo_pol;
		for(unsigned j = 0; j < polygons[i].size(); j++){
			ClipperLib::IntPoint punto(polygons[i][j].X, polygons[i][j].Y);
			nuevo_pol.push_back(punto);
		}

		_clipperPolygons->push_back(nuevo_pol);
	}
}

Polygon::Polygon(vector<Contour> poligonos){
	_contornos = poligonos;
	_clipperPolygons = NULL;
}

Polygon::~Polygon(){
	freeMem();
}

Polygon::Polygon(const Polygon & pol){
	copiarDesde(pol);
}

Polygon &
Polygon::operator =(const Polygon & pol){
	if(this != &pol){
		freeMem();
		copiarDesde(pol);
	}

	return *this;
}

void
Polygon::addVertex(Vector2 vertice, unsigned index){
	if(index < _contornos.size()){
		_contornos[index].push_back(vertice);
	}
}

void Polygon::setContour(Contour vertices, unsigned index){
	if(index >= _contornos.size()){
		int dif = index - _contornos.size();

		for(int i = 0; i <= dif; i++){
			Contour nuevo;
			_contornos.push_back(nuevo);
		}
	}

	_contornos[index].clear();

	_contornos[index] = vertices;
}

Contour
Polygon::getContour(unsigned index){
	Contour res;

	if(index < _contornos.size()){
		res = _contornos[index];
	}

	return res;
}

void
Polygon::copiarDesde(const Polygon & pol){
	for(unsigned i = 0; i < pol._contornos.size(); i++){
		Contour nuevo;

		for(unsigned j = 0; j < pol._contornos[i].size(); j++){
			nuevo.push_back(pol._contornos[i][j]);
		}

		_contornos.push_back(nuevo);
	}

	if(pol._clipperPolygons != NULL){
		_clipperPolygons = new ClipperLib::Polygons(*(pol._clipperPolygons));
	}else{
		_clipperPolygons = NULL;
	}
}

void
Polygon::setContours(vector<Contour> poligonos){
	freeMem();

	_contornos = poligonos;
}

vector<Contour>
Polygon::getContours(){
	return _contornos;
}

ClipperLib::Polygons
Polygon::getClipperPolygons() const{
	ClipperLib::Polygons res;

	if(_clipperPolygons == NULL){
		for(unsigned i = 0; i < _contornos.size(); i++){
			ClipperLib::Polygon nuevo;
			res.push_back(nuevo);
			for(unsigned j = 0; j < _contornos[i].size(); j++){
				ClipperLib::IntPoint nuevo_punto(_contornos[i][j].getX(), _contornos[i][j].getY());
				res[i].push_back(nuevo_punto);
			}
		}
	}else{
		res = *(_clipperPolygons);
	}

	return res;
}

void
Polygon::freeMem(){
	_contornos.clear();

	if(_clipperPolygons != NULL){
		_clipperPolygons->clear();
		delete _clipperPolygons;
		_clipperPolygons = NULL;
	}
}

Polygon
Polygon::Union(const Polygon& pol) const{

	ClipperLib::Clipper clipper;
	clipper.AddPolygons(getClipperPolygons(), ClipperLib::ptSubject);
	clipper.AddPolygons(pol.getClipperPolygons(), ClipperLib::ptClip);

	ClipperLib::Polygons res;

	clipper.Execute(ClipperLib::ctUnion, res);

	return Polygon(res);
}

Polygon
Polygon::OuterUnion(const Polygon& pol) const{
	ClipperLib::Clipper clipper;
	ClipperLib::ExPolygons exRes;

	clipper.AddPolygons(getClipperPolygons(), ClipperLib::ptSubject);
	clipper.AddPolygons(pol.getClipperPolygons(), ClipperLib::ptClip);

	clipper.Execute(ClipperLib::ctUnion, exRes);

	ClipperLib::Polygons res;

	for(unsigned i = 0; i < exRes.size(); i++){
		res.push_back(exRes[i].outer);
	}

	return Polygon(res);
}

Polygon
Polygon::Interseccion(const Polygon& pol) const{
	ClipperLib::Clipper clipper;
	clipper.AddPolygons(getClipperPolygons(), ClipperLib::ptSubject);
	clipper.AddPolygons(pol.getClipperPolygons(), ClipperLib::ptClip);
	ClipperLib::Polygons res;

	clipper.Execute(ClipperLib::ctIntersection, res);

	return Polygon(res);
}

Polygon
Polygon::OuterInterseccion(const Polygon& pol) const{
	ClipperLib::Clipper clipper;
	ClipperLib::ExPolygons exRes;

	clipper.AddPolygons(getClipperPolygons(), ClipperLib::ptSubject);
	clipper.AddPolygons(pol.getClipperPolygons(), ClipperLib::ptClip);

	clipper.Execute(ClipperLib::ctIntersection, exRes);

	ClipperLib::Polygons res;

	for(unsigned i = 0; i < exRes.size(); i++){
		res.push_back(exRes[i].outer);
	}

	return Polygon(res);
}

Polygon
Polygon::Diferencia(const Polygon& pol) const{

	ClipperLib::Clipper clipper;
	clipper.AddPolygons(getClipperPolygons(), ClipperLib::ptSubject);
	clipper.AddPolygons(pol.getClipperPolygons(), ClipperLib::ptClip);
	ClipperLib::Polygons res;

	clipper.Execute(ClipperLib::ctDifference, res);

	return Polygon(res);
}

Polygon
Polygon::OuterDiferencia(const Polygon& pol) const{
	ClipperLib::Clipper clipper;
	ClipperLib::ExPolygons exRes;

	clipper.AddPolygons(getClipperPolygons(), ClipperLib::ptSubject);
	clipper.AddPolygons(pol.getClipperPolygons(), ClipperLib::ptClip);

	clipper.Execute(ClipperLib::ctDifference, exRes);

	ClipperLib::Polygons res;

	for(unsigned i = 0; i < exRes.size(); i++){
		res.push_back(exRes[i].outer);
	}

	return Polygon(res);
}

Polygon
Polygon::Xor(const Polygon& pol) const{

	ClipperLib::Clipper clipper;
	clipper.AddPolygons(getClipperPolygons(), ClipperLib::ptSubject);
	clipper.AddPolygons(pol.getClipperPolygons(), ClipperLib::ptClip);
	ClipperLib::Polygons res;

	clipper.Execute(ClipperLib::ctXor, res);

	return Polygon(res);
}

Polygon
Polygon::OuterXor(const Polygon& pol) const{
	ClipperLib::Clipper clipper;
	ClipperLib::ExPolygons exRes;

	clipper.AddPolygons(getClipperPolygons(), ClipperLib::ptSubject);
	clipper.AddPolygons(pol.getClipperPolygons(), ClipperLib::ptClip);

	clipper.Execute(ClipperLib::ctXor, exRes);

	ClipperLib::Polygons res;

	for(unsigned i = 0; i < exRes.size(); i++){
		res.push_back(exRes[i].outer);
	}

	return Polygon(res);
}

Polygon
Polygon::Expandir(float expansion) const{
	ClipperLib::Polygons resultado;

	ClipperLib::OffsetPolygons(getClipperPolygons(), resultado, expansion, ClipperLib::jtMiter);
	Polygon pol_res(resultado);

	return pol_res;
}

vector<vector<p2t::Point*> >
Polygon::getPoly2TriPolygons() const {
	vector<vector<p2t::Point*> > res;

	for(unsigned i = 0; i < _contornos.size(); i++){
		vector<p2t::Point*> nuevo;

		for(unsigned j = 0; j < _contornos[i].size(); j++){
			nuevo.push_back(new p2t::Point(_contornos[i][j].getX(), _contornos[i][j].getY()));
		}

		res.push_back(nuevo);
	}

	return res;
}

bool
Polygon::isVacio() const{
	return _contornos.empty();
}

int
Polygon::getContoursNumber() const{
	return _contornos.size();
}

int
Polygon::getNumVertices() const{
	int num_vertices = 0;
	for(int i = 0; i < _contornos.size(); i++){
		num_vertices += _contornos[i].size();
	}

	return num_vertices;
}

} /* namespace candy */
