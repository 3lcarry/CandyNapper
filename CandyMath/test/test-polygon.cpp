#include "CandyMath.h"
#include "CandyGraphics.h"

using namespace std;
using namespace candy;

void DrawPolygon(Polygon p, Transformation* tPoligono, Color c){
	for(int i = 0; i < p.getContoursNumber(); i++){
		Contour vertices = p.getContour(i);

		for(unsigned i = 0; i < vertices.size(); i++){
			tPoligono->addLine(vertices[i], vertices[(i+1)%vertices.size()], Color(0, 0, 0, 1), false);
		}

		for(unsigned i = 0; i < vertices.size(); i++){
			Transformation* tPunto = tPoligono->addTransformation();
			tPunto->Scale(0.5, 0.5);
			tPunto->Translate(vertices[i]);
			tPunto->addShape(4, c);
		}
	}
}

Contour makeCuadrado(Vector2 position, float size = 100){
	float half_size = size / 2.0;

	float x = position.getX();
	float y = position.getY();

	Contour v2;

	v2.push_back(Vector2(x + half_size, y + half_size));
	v2.push_back(Vector2(x - half_size, y + half_size));
	v2.push_back(Vector2(x - half_size, y - half_size));
	v2.push_back(Vector2(x + half_size, y - half_size));

	return v2;
}

int main(int argc, char **argv) {
	Contour v;
	v.push_back(Vector2(0, 100));
	v.push_back(Vector2(0, 0));
	v.push_back(Vector2(100, 0));
	v.push_back(Vector2(100, 100));
	Polygon p(v);

	/*
	Contour v2;
	v2.push_back(new Vector2(50, 50));
	v2.push_back(new Vector2(-50, 50));
	v2.push_back(new Vector2(-50, -50));
	v2.push_back(new Vector2(50, -50));
	*/
	//Polygon p2(makeCuadrado(Vector2(0, 0), 400));
	Polygon p2 = PolygonFactory::Poligono(Vector2(0, 0), 50, 20);

	Polygon p3;

	//Init de la parte grafica
	float ancho_v = 800;
	float alto_v = 600;
	Teclado tec;
	Ventana* ventana = new Ventana(ancho_v, alto_v, "Test poligonos");
	CandyGraphics cg;
	cg.InitOpenGL();
	cg.setClearColor(Color(1, 1, 1, 1));
	Scene* escena = cg.getScenePtr();
	Camera* cam2D = escena->addCamera2D(-ancho_v / 2.0, ancho_v/2.0, -alto_v/2.0, alto_v/2.0);
	cam2D->setLight(false);
	cam2D->setDepth(false);
	Transformation* tEscena = cam2D->addTransformation();
	Transformation* tPol1 = tEscena->addTransformation();
	Transformation* tPol2 = tEscena->addTransformation();
	Transformation* tPol3 = tEscena->addTransformation();
	Transformation* tPolExp = tEscena->addTransformation();

	//Dibujamos el poligono 1
	DrawPolygon(p, tPol1, Color::Red);

	//Dibujamos el poligono 2
	DrawPolygon(p2, tPol2, Color::Green);

	//DrawPolygon(p3, tPol3, Color::Blue);

	bool bUnion = false;
	bool bInterseccion = false;
	bool bDiferencia = false;
	bool bXor = false;

	int iTime = 0;
	while(!ventana->isClosing()){
		ventana->Update();

		if(tec.isPulsada(Teclado::U)){
			if(iTime >= 100){
				//Union
				p3 = p.Union(p2);
				tPol3->rmChilds();
				DrawPolygon(p3, tPol3, Color::Blue);
				iTime = 0;

				bUnion = true;
				bInterseccion = false;
				bDiferencia = false;
				bXor = false;
			}
		}

		if(tec.isPulsada(Teclado::I)){
			if(iTime >= 100){
				//Interseccion
				p3 = p2.Interseccion(p);
				tPol3->rmChilds();
				DrawPolygon(p3, tPol3, Color::Blue);
				iTime = 0;

				bInterseccion = true;
				bUnion = false;
				bDiferencia = false;
				bXor = false;
			}
		}

		if(tec.isPulsada(Teclado::D)){
			if(iTime >= 100){
				//Union
				p3 = p2.Diferencia(p);
				tPol3->rmChilds();
				DrawPolygon(p3, tPol3, Color::Blue);
				iTime = 0;

				bDiferencia = true;
				bUnion = false;
				bInterseccion = false;
				bXor = false;
			}
		}

		if(tec.isPulsada(Teclado::X)){
			if(iTime >= 100){
				//Union
				p3 = p2.Xor(p);
				tPol3->rmChilds();
				DrawPolygon(p3, tPol3, Color::Blue);
				iTime = 0;

				bXor = true;
				bDiferencia = false;
				bUnion = false;
				bInterseccion = false;
			}
		}

		if(tec.isPulsada(Teclado::E)){
			if(iTime >= 100){
				//Expandimos el primero
				tPolExp->rmChilds();
				DrawPolygon(p3.Expandir(10), tPolExp, Color::Magenta);

				iTime = 0;
			}
		}

		if(Raton::isPressed(Raton::Derecho)){
			Vector2 pos_r = Raton::getPosition(ventana);
			Vector2 nueva_pos = Vector2(pos_r.getX() - ancho_v/2.0, pos_r.getY() - alto_v/2.0);

			tPol2->rmChilds();
			p2.setContour(makeCuadrado(nueva_pos));
			DrawPolygon(p2, tPol2, Color::Green);

			tPol3->rmChilds();

			if(bDiferencia){
				p3 = p.Diferencia(p2);
			}

			if(bUnion){
				p3 = p.Union(p2);
			}

			if(bInterseccion){
				p3 = p.Interseccion(p2);
			}

			if(bXor){
				p3 = p.Xor(p2);
			}

			DrawPolygon(p3, tPol3, Color::Blue);
		}

		if(Raton::isPressed(Raton::Izquierdo)){
			Vector2 pos_r = Raton::getPosition(ventana);
			Vector2 nueva_pos = Vector2(pos_r.getX() - ancho_v/2.0, pos_r.getY() - alto_v/2.0);

			tPol1->rmChilds();
			p.setContour(makeCuadrado(nueva_pos));
			DrawPolygon(p, tPol1, Color::Red);

			tPol3->rmChilds();

			if(bDiferencia){
				p3 = p2.Diferencia(p);
			}

			if(bUnion){
				p3 = p.Union(p2);
			}

			if(bInterseccion){
				p3 = p2.Interseccion(p);
			}

			if(bXor){
				p3 = p2.Xor(p);
			}

			DrawPolygon(p3, tPol3, Color::Blue);
		}

		iTime++;

		cg.Render();

		ventana->Display();
	}

}
