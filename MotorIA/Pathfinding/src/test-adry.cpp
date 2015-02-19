#include "IPathfinding.h"
#include "CandyGraphics.h"
#include "poly2tri/poly2tri.h"
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>

using namespace std;
using namespace candy;

Vector3 point2vector3(p2t::Point* p){
	return Vector3(p->x, p->y, 0);
}

void DrawPolygon(Polygon p, Transformation* tPoligono, Color c){
	vector<candy::Contour> poligonos = p.getContours();

	for(unsigned j = 0; j < poligonos.size(); j++){
		Contour vertices = poligonos[j];

		for(unsigned i = 0; i < vertices.size(); i++){
			tPoligono->addLine(vertices[i], vertices[(i+1)%vertices.size()], Color::Black, false);
		}

		for(unsigned i = 0; i < vertices.size(); i++){
			Transformation* tPunto = tPoligono->addTransformation();
			tPunto->Scale(0.5, 0.5);
			tPunto->Translate(vertices[i]);
			tPunto->addShape(4, c);
		}
	}
}

int main(int argc, char **argv) {

	Timer::Init();
	/* initialize random seed: */
	srand ( time(NULL) );

	//IPathfinding* ip = IPathfinding::Instance();

	float ancho_p = 400;
	float alto_p = 400;
	//ip->Init(ancho_p, alto_p, 5);
	IPathfinding* ip = new IPathfinding(ancho_p, alto_p, 5);


	/*Contour hole;
	hole.push_back(Vector2(195,0));
	hole.push_back(Vector2(180,0));
	hole.push_back(Vector2(180,-5));
	hole.push_back(Vector2(195,-5));

	ip->AddObstaculo(hole);*/
	/*
	for(int i=0;i<200;i++){
		/*int x=rand()%200, y=rand()%200,tam=10;
		if(Timer::getTimeElapsed()%2 == 0){
			x = -x;
		}
		else if(Timer::getTimeElapsed()%3 == 0){
			y = -y;
		}
		int tam = 10;
		int x = 150-i, y = 150-i;
		Contour hole;
		hole.push_back(Vector2(x + tam,y + tam));
		hole.push_back(Vector2(x - tam,y + tam));
		hole.push_back(Vector2(x - tam,y - tam));
		hole.push_back(Vector2(x + tam,y - tam));

		Polygon obstaculo(hole);

		ip->AddObstaculo(hole);
	}
	*/
	int numObstaculos = 0;
	srand(time(0));
	for(int i =0; i<10;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		ip->AddObstaculo(PolygonFactory::Cuadrado(Vector2(x, y), 1.0, 1.0));
		numObstaculos++;
	}

	for(int i =0; i<10;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		ip->AddObstaculo(PolygonFactory::Cuadrado(Vector2(x, y), 1.0, 1.0));
		numObstaculos++;
	}

	for(int i =0; i<10;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		ip->AddObstaculo(PolygonFactory::Cuadrado(Vector2(x, y), 1.0, 1.0));
		numObstaculos++;
	}
	for(int i =0; i<10;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		ip->AddObstaculo(PolygonFactory::Cuadrado(Vector2(x, y), 1.0, 1.0));
		numObstaculos++;
	}

	for(int i =0; i<15;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		ip->AddObstaculo(PolygonFactory::Cuadrado(Vector2(x, y), 1.0, 1.0));
		numObstaculos++;
	}

	for(int i =0; i<5;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		ip->AddObstaculo(PolygonFactory::Cuadrado(Vector2(x, y), 1.0, 1.0));
		numObstaculos++;
	}

	for(int i =0; i<5;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		ip->AddObstaculo(PolygonFactory::Cuadrado(Vector2(x, y), 1.0, 1.0));
		numObstaculos++;
	}

	for(int i =0; i<15;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		ip->AddObstaculo(PolygonFactory::Cuadrado(Vector2(x, y), 1.0, 1.0));
		numObstaculos++;
	}

	cout << "[MotorIA/test-adry.cpp] Numero de obstaculos: " << numObstaculos << endl;
	ip->GenerarGrafo();


	Grafo* grafo = ip->getGrafo();
	vector<Nodo*> nodos = grafo->getGrafo();


	//Init de la parte grafica

	float ancho_v = 800;
	float alto_v = 600;

	Teclado teclado;
	Ventana* v = new Ventana(ancho_v, alto_v, "Prueba Pathfinding");
	CandyGraphics* cg = new CandyGraphics();
	cg->InitOpenGL();
	cg->setClearColor(Color(1.0, 1.0, 1.0, 1.0));

	Scene* escena = cg->getScenePtr();

	Camera* cCam2D = escena->addCamera2D(-ancho_v/2.0, ancho_v/2.0, -alto_v/2.0, alto_v/2.0);
	cCam2D->setLight(false);
	cCam2D->setDepth(false);

	Transformation* tEscena = cCam2D->addTransformation();

	Transformation* tTitle = cCam2D->addTransformation();
	tTitle->Translate(-ancho_v/2.0 + 50, alto_v/2.0 - 50);
	Text* teTitle = tTitle->addText();
	teTitle->setColor(Color(0.0, 0.0, 0.0, 1.0));
	teTitle->setTamanyo(20);
	teTitle->setTexto("Pathfinding");

	Transformation* tTextCamino = cCam2D->addTransformation();
	tTextCamino->Translate(-ancho_v/2.0 + 50, -alto_v/2.0 + 50);
	Text* teCamino = tTextCamino->addText();
	teCamino->setColor(Color(0, 0, 0, 1));
	teCamino->setTamanyo(15);
	teCamino->setTexto("No hay camino");

	Transformation* tCamino = tEscena->addTransformation();

	Transformation* tTriang = cCam2D->addTransformation();


	vector<p2t::Triangle*> t = grafo->getTriangulos();
	for(unsigned i = 0; i < t.size(); i++){
		for(int j = 0; j < 3; j++){
			p2t::Point* p = t[i]->GetPoint(j);

			tTriang->addLine(point2vector3(p), point2vector3(t[i]->GetPoint((j+1) % 3)), Color::Red, false);

			Transformation* tPol = tTriang->addTransformation();
			tPol->Translate(point2vector3(p));
			tPol->Scale(0.5, 0.5);
			tPol->addShape(10, Color(1, 1, 0, 1));
		}
	}


	Transformation* tGrafo = cCam2D->addTransformation();

	for(unsigned i = 0; i < nodos.size(); i++){
		vector<Nodo*> nodos_ady = nodos[i]->getNodosAdy();
		for(unsigned j = 0; j < nodos_ady.size(); j++){
			//Dibujamos las aristas del nodo
			tGrafo->addLine(nodos[i]->getPosition(), nodos_ady[j]->getPosition(), Color(0, 0, 1, 1), false);
		}

		Transformation* tPol = tGrafo->addTransformation();
		tPol->Translate(nodos[i]->getPosition());
		tPol->Scale(0.5, 0.5);
		tPol->addShape(4, Color(0, 1, 0, 1));
	}


	Transformation* tObst = cCam2D->addTransformation();
	vector<Polygon> obst = ip->getObstaculos();
	for(unsigned i = 0; i < obst.size(); i++){
		DrawPolygon(obst[i], tObst, Color::Cyan);
	}

	Transformation* tContorno = tEscena->addTransformation();
	DrawPolygon(ip->getContorno(), tContorno, Color::Black);

	bool bContorno = true;
	bool bTriangulos = true;
	bool bGrafo = true;
	bool bObst = true;

	bool bInicio = false;
	bool bFinal = false;

	bool bCamino = false;

	Vector2 inicio;
	Vector2 final;

	long int iTime = 0;

	tGrafo->setActive(false);
	tTriang->setActive(false);

	while(!v->isClosing()){
		v->Update();

		//CHECK TECLADO
		long int tiempo = Timer::getTimeElapsed();
		if(tiempo - iTime > 100){
			iTime = tiempo;
			if(teclado.isPulsada(Teclado::C)){
					if(bContorno){
						bContorno = false;
						tContorno->setActive(false);
					}else{
						bContorno = true;
						tContorno->setActive(true);
					}
			}

			if(teclado.isPulsada(Teclado::T)){
					if(bTriangulos){
						bTriangulos = false;
						tTriang->setActive(false);
					}else{
						bTriangulos = true;
						tTriang->setActive(true);
					}
			}

			if(teclado.isPulsada(Teclado::G)){
					if(bGrafo){
						bGrafo = false;
						tGrafo->setActive(false);
					}else{
						bGrafo = true;
						tGrafo->setActive(true);
					}
			}

			if(teclado.isPulsada(Teclado::E)){
					if(bObst){
						bObst = false;
						tObst->setActive(false);
					}else{
						bObst = true;
						tObst->setActive(true);
					}
			}
		}

		//CHECK MOUSE
		if(Raton::isPressed(Raton::Izquierdo)){
			bInicio = true;

			Vector2 pos = Raton::getPosition(v);
			inicio.setX(pos.getX() - ancho_v / 2.0);
			inicio.setY(pos.getY() - alto_v / 2.0);

			if(bFinal){
				bCamino = true;
			}
		}

		if(Raton::isPressed(Raton::Derecho)){
			bFinal = true;

			Vector2 pos = Raton::getPosition(v);
			final.setX(pos.getX() - ancho_v / 2.0);
			final.setY(pos.getY() - alto_v / 2.0);

			if(bInicio){
				bCamino = true;
			}
		}

		iTime++;

		if(bCamino){
			//Recalculo el camino
			bCamino = false;

			ostringstream form;
			form << "De " << inicio << " A " << final;
			teCamino->setTexto(form.str());

			tCamino->rmChilds();

			vector<Nodo*> camino = ip->CalcularCamino(inicio, final);

			for(unsigned i = 0; i < camino.size(); i++){
				if(i != camino.size() - 1){
					tCamino->addLine(camino[i]->getPosition(), camino[i+1]->getPosition(), Color(0.7, 0.5, 0, 1), false);
				}

				Transformation* tPol = tCamino->addTransformation();
				tPol->Scale(0.5, 0.5);
				tPol->Translate(camino[i]->getPosition());
				tPol->addShape(6, Color(0.5, 0, 1, 1));
			}
		}

		//Render de la parte grafica
		cg->Render();

		v->Display();
	}

}
