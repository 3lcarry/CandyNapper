/*
 * Menu.h
 *
 *  Created on: 06/03/2012
 *      Author: carrillo
 */

#ifndef MENU_H_
#define MENU_H_

//#include "CandyGraphics.h"
#include "InterfazGraphics.h"
#include <iostream>
using namespace std;
#include <list>

namespace candy {

struct Buttons{
	Transformation* _Position;
	guiButton* _Boton;
};


class Menu {
public:

	enum Botones{
		P_ComenzarPartida = 10,
		P_Salir = 11,
		P_Cargar,
		P_PartidaRapida,
		I_Continuar,
		I_MenuPrincipal,
		I_Salir,
		CL_Continuar,
		CL_Guardar,
		I_Guardar,
		I_Reintentar
	};

	Menu(Scene* escena, Ventana* v, string titulo,int tam=25);

	virtual ~Menu();

	Camera* getMenuCamera();

	void addButton(Vector2 pos, string texto ,int id, int width,int heigth);

	bool deleteButton(int id);

	void setFondo(int textura);

	void setFondo(Color color);

private:
	Plane* _fondo;
	float _ancho, _alto;
	Camera* _Cam2D;
	list<Buttons*> _botones;
};

} /* namespace candy */
#endif /* MENU_H_ */
