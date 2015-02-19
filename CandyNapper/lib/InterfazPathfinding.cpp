/*
 * InterfazPathfinding.cpp
 *
 *  Created on: 22/03/2012
 *      Author: esteve
 */

#include "InterfazPathfinding.h"

namespace candy {

InterfazPathfinding* InterfazPathfinding::_instance = NULL;

InterfazPathfinding* InterfazPathfinding::getInstance(){

	if(_instance == NULL){
		_instance = new InterfazPathfinding();
	}

	return _instance;
}

InterfazPathfinding::InterfazPathfinding() {
	_pathfinding = NULL;
}

InterfazPathfinding::~InterfazPathfinding() {
	delete _pathfinding;
}

void InterfazPathfinding::GenerarGrafo(){
	if(_pathfinding != NULL){
		delete _pathfinding;
		_pathfinding = NULL;
	}

	_pathfinding = new IPathfinding(400, 400, 10); //ver de donde se saca el tama√±ano de mapa


	list<GEStatic*> obs = CandyNapper::getInstancia()->getEm()->getStatics();
	list<GEStatic*>::iterator i;
	for(i = obs.begin(); i != obs.end(); i++){
		Vector2 posicion = AdapCoordJ2P((*i)->getPosicion());
		Polygon poligono = PolygonFactory::Cuadrado(posicion, 1.0, 1.0); //Cambiar los tamaños
		//cout << "[InterfazPathfinding.cpp] Añado un obstaculo: " << poligono << endl;
		_pathfinding->AddObstaculo(poligono);
	}
	//cout << "[InterfazPathfinding.cpp] Numero de obstaculos: " << obs.size() << endl;

	_pathfinding->GenerarGrafo();
}

vector<Vector3> InterfazPathfinding::ObtCamino(Vector3 init, Vector3 fin){
	vector<Vector3> caminoG;
	vector<Nodo*> caminoP = _pathfinding->CalcularCamino(AdapCoordJ2P(init), AdapCoordJ2P(fin));


	for(unsigned int i = 0; i < caminoP.size(); i++){
		caminoG.push_back(AdapCoordP2J(caminoP[i]->getPosition()));
	}

	return caminoG;
}

Vector3 InterfazPathfinding::Suavizado(vector<Vector3> &camino, GEDynamic* entity){
	bool seLlega = false;
	Vector3 sigPos;
	//int cont = 1;

	if(!camino.empty()){
		Vector3 init = camino[0];
		vector<Vector3>::reverse_iterator i;
		for(i = camino.rbegin(); i != camino.rend() && !seLlega; i++){
			/*cout<<endl;
			cout<<"InterfazPathfinding: tiempo"<<Timer::getTimeElapsed()<<endl;
			cout<<"InterfazPathfinding: init"<<init<<endl;
			cout<<"InterfazPathfinding: fin "<<(*i)<<endl;*/

			Vector3 posAct = entity->getPosicion();
			int radio =  entity->getRadio();
			double angMovi = entity->getVisionX() + entity->getAnguloMovimiento();
			if(angMovi != angMovi)
				angMovi = 0;
			double ang1 = angMovi + M_PI/2;
			double ang2 = angMovi - M_PI/2;
			double ang3 = angMovi + M_PI;

			//Puntos que envuelven al enemigo;
			Vector3 point1(posAct.getX()+cos(angMovi)*radio, 0, posAct.getZ()+sin(angMovi)*radio);
			Vector3 point2(posAct.getX()+cos(ang1)*radio, 0, posAct.getZ()+sin(ang1)*radio);
			Vector3 point3(posAct.getX()+cos(ang2)*radio, 0, posAct.getZ()+sin(ang2)*radio);
			Vector3 point4(posAct.getX()+cos(ang3)*radio, 0, posAct.getZ()+sin(ang3)*radio);

			/*cout<<"InterfazPathfinding: angMovi "<<angMovi<<endl;
			cout<<"InterfazPathfinding: posAct "<<posAct<<endl;
			cout<<"InterfazPathfinding: point1 "<<point1<<endl;
			cout<<"InterfazPathfinding: point2 "<<point2<<endl;
			cout<<"InterfazPathfinding: point3 "<<point3<<endl;
			cout<<"InterfazPathfinding: point4 "<<point4<<endl;*/

			if(!InterfazPhysics::getInstance()->obstaculo(posAct, (*i))){
				if(!InterfazPhysics::getInstance()->obstaculo(point1, (*i)) && !InterfazPhysics::getInstance()->obstaculo(point2, (*i))
						&& !InterfazPhysics::getInstance()->obstaculo(point3, (*i)) && !InterfazPhysics::getInstance()->obstaculo(point4, (*i))){

					//cout<<"InterfazPathfinding: NO HAY OBSTACULO"<<endl;
					seLlega = true;
					sigPos = (*i);
				}
			}
			//else {
				//cout<<"InterfazPathfinding: HAY OBSTACULO"<<endl;
			//}
			//cont++;
		}
		if(!seLlega)
			throw -1;

		//camino.erase(camino.begin(), camino.begin() + (camino.size() - cont));
	}
	else{
		throw -1;
	}

	if(sigPos == entity->getPosicion()){
		throw -1;
	}
	//cout<<"InterfazPathfinding: sigPos "<<sigPos<<endl;

	return sigPos;
}

double InterfazPathfinding::ObtAngulo(Vector3 a, Vector3 b){
	double h;
	double co;

	h = sqrt(((a.getX() - b.getX()) * (a.getX() - b.getX())) + ((a.getZ() - b.getZ()) * (a.getZ() - b.getZ())));
	co = abs(b.getZ() - a.getZ());

	double angulo = asin(co/h);

	if(a.getX() >= b.getX() && a.getZ() >= b.getZ())
		angulo = M_PI - angulo;
	else if(a.getX() >= b.getX() && a.getZ() <= b.getZ())
		angulo += M_PI;
	else if(a.getX() <= b.getX() && a.getZ() <= b.getZ())
		angulo = -angulo;

	double result = angulo - (M_PI/2);

	while(result < 0){
		result += 2*M_PI;
	}
	while(result > 2*M_PI){
		result -= 2*M_PI;
	}

	return  result;
}

bool InterfazPathfinding::EsTransitable(Vector3 pos){
	bool dentro = false;
	vector<p2t::Triangle*> triangulos = _pathfinding->getGrafo()->getTriangulos();

	/*for(int i = 0;  i < triangulos.size(); i++){
		if(triangulos[i]->IsInterior()){
			cout<<"Triangulo "<<i<<endl;
			for(int j = 0; j < 3; j++){
				p2t::Point* vertice = triangulos[i]->GetPoint(j);
				cout<<"Vertice "<<j<<" ("<<vertice->x<<", "<<vertice->y<<")"<<endl;
			}
			cout<<endl;
		}
	}*/

	//cout<<"InterfazPathfinding: pos = "<<pos<<endl;

	Vector2 posP = AdapCoordJ2P(pos);
	p2t::Point* point = new p2t::Point(posP.getX(), posP.getY());

	for(int i = 0; i < triangulos.size() && !dentro; i++){
		if(triangulos[i]->EstaDentro(point) && triangulos[i]->IsInterior()){
			dentro = true;
		}
	}

	delete point; point = NULL;

	/*if(dentro)
		cout<<"InterfazPathfinding: Esta Dentro"<<endl;
	else
		cout<<"InterfazPathfinding: NO esta dentro"<<endl;*/

	return dentro;
}

IPathfinding* InterfazPathfinding::getIPathfinding(){
	return _pathfinding;
}

Vector3 InterfazPathfinding::AdapCoordP2J(Vector2 v){
	Vector3 v3(v.getX(), 0.0, -v.getY());
	return v3;
}

Vector2 InterfazPathfinding::AdapCoordJ2P(Vector3 v){
	Vector2 v2(v.getX(), -v.getZ());
	return v2;
}

Vector3* InterfazPathfinding::AdapCoordP2J(Vector2* v){
	Vector3* v3 = new Vector3(v->getX(), 0.0, -v->getY());
	return v3;
}

Vector2* InterfazPathfinding::AdapCoordJ2P(Vector3* v){
	Vector2* v2 = new Vector2(v->getX(), -v->getZ());
	return v2;
}
}
