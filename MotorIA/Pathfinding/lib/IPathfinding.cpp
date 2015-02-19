/*
 * IPathfinding.cpp
 *
 *  Created on: 24/02/2012
 *      Author: esteve
 */

#include "IPathfinding.h"
#include "Pathfinding.h"

namespace candy{

/*IPathfinding* IPathfinding::pInstance = NULL;

IPathfinding* IPathfinding::Instance(){

	if(pInstance == NULL){
		pInstance = new IPathfinding();
	}
	return pInstance;

}*/

void IPathfinding::Init(double mapX_, double mapY_,double exp_){
	exp = exp_;
	grafo = NULL;

	//Creamos el contorno
	Contour contorno;
	float half_x = mapX_ / 2.0;
	float half_y = mapY_ / 2.0;
	contorno.push_back(Vector2(-half_x, -half_y));
	contorno.push_back(Vector2(half_x, -half_y));
	contorno.push_back(Vector2(half_x, half_y));
	contorno.push_back(Vector2(-half_x, half_y));

	_contorno = Polygon(contorno); //Poligono con el contorno
}

IPathfinding::IPathfinding(double mapX_, double mapY_, double exp_){
	Init(mapX_, mapY_, exp_);
}

IPathfinding::~IPathfinding(){
	if(grafo != NULL){
		delete grafo;
		grafo = NULL;
	}
}

void IPathfinding::AddObstaculo(Polygon polygono){

	//Obstaculo* obs = new Obstaculo(vertices, exp);

	Obstaculos.push_back(polygono);
}

void IPathfinding::GenerarGrafo(){
	if(grafo == NULL){
		vector<Polygon> polyg_expandidos;

		//Primero tenemos que expandir
		for(unsigned i = 0; i < Obstaculos.size(); i++){
			polyg_expandidos.push_back(Obstaculos[i].Expandir(exp));
		}


		_contorno = _contorno.Expandir(-1);
		bool toca;
		do{
			toca = false;
			vector<Polygon>::iterator it = polyg_expandidos.begin();
			while(it != polyg_expandidos.end()){
				int nObstaculo = it->getNumVertices();
				int nContorno = _contorno.getNumVertices();

				int nUnion = _contorno.Union((*it)).getNumVertices();


				if(nUnion > nContorno){
					_contorno = _contorno.Diferencia((*it));
					toca = true;
					it = polyg_expandidos.erase(it);
				}else{
					it++;
				}
			}
		}while(toca);
		_contorno = _contorno.Expandir(1);


		p2t::CDT cdt(_contorno.getPoly2TriPolygons()[0]);

		//Luego unir todos los obstaculos
		Polygon union_obstaculos;
		//Primero tenemos que expandir
		for(unsigned i = 0; i < polyg_expandidos.size(); i++){
			union_obstaculos = union_obstaculos.Union(polyg_expandidos[i]);
		}

		vector<vector<p2t::Point*> > union_p2t = union_obstaculos.getPoly2TriPolygons();
		for(unsigned i = 0; i < union_p2t.size(); i++){
			cdt.AddHole(union_p2t[i]);
		}
		cdt.Triangulate();
		grafo = new Grafo(cdt.GetTriangles());
	}
}

Grafo* IPathfinding::getGrafo() const{
	return grafo;
}


vector<Nodo*> IPathfinding::CalcularCamino(Vector2 init, Vector2 fin){

	vector<Nodo*> g;

	if(grafo != NULL){
		//cout<<"IPathfinding: CalcularCamino"<<endl;
		grafo->Reset();
		//cout<<grafo->getGrafo().size()<<endl;
		Pathfinding path(grafo);
		//cout<<"IPathfinding grafo "<<grafo->getGrafo().size()<<endl;
		path.Calcular(init, fin);
		g = path.getCamino();
	}

	return g;

}

vector<Polygon> IPathfinding::getObstaculos() const{
	return Obstaculos;
}

Polygon IPathfinding::getContorno() const{
	return _contorno;
}

}
