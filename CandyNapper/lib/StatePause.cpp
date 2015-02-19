/*
 * PauseState.cpp
 *
 *  Created on: Nov 25, 2011
 *      Author: carrillo
 */

#include "StatePause.h"
#include "CandyNapper.h"
#include "InterfazGraphics.h"
#include "StateMachineGame.h"
#include <iostream>
#include <vector>
#include "Raton.h"
#include "Menu.h"
#include "Application.h"
using namespace std;

namespace candy {

StatePause::StatePause() :
		State(StateMachineGame::Pause)
{
	_ig = InterfazGraphics::getInstance();
	_salir = false;
	_continuar = false;
	_menuPrincipal = false;
}

StatePause::~StatePause() {
}

void StatePause::Transition() {

	if (_ig->getVentana()->isClosing() || _salir) {
		SM->ChangeState(StateMachineGame::Exit);
	} else if (_continuar) {
		_ig->visibilidadMenuIngame(false);
		SM->ChangeState(StateMachineGame::Play);
	} else if (_menuPrincipal) {

		_ig->visibilidadMenuPrincipal(true);
		_ig->visibilidadHUD(false);
		_ig->visibilidadMenuIngame(false);
		_ig->visibilidadWorld(false);

		InterfazMusic::getInstancia()->desactivarMusicaFondo();
		InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Menu);
		SM->ChangeState(StateMachineGame::Menu);
	}

}

void StatePause::Execute() {
	_salir = false;
	_continuar = false;
	_menuPrincipal = false;

	//Actualizamos eventos de ventana en motor grafico
	_ig->getVentana()->Update();

	//Decodifica los comandos de la consola
	decodeConsole();

	//Comprobar botones
	comprobarBotones();

	//Renderizamos el motor grafico
	_ig->Render();

	//Hacer metodo para parar la musica

	//Mostramos el resultado del renderizado
	_ig->getVentana()->Display();
}

void StatePause::comprobarBotones() {
	if (Raton::isPressed(Raton::Izquierdo)) {
		int seleccion = _ig->seleccionMenuIngame();
		//cout << "[StatePause.cpp] Seleccion: " << seleccion << endl;

		if (seleccion == Menu::I_Continuar)
			_continuar = true;

		if(seleccion == Menu::I_MenuPrincipal)
			_menuPrincipal = true;

		if (seleccion == Menu::I_Salir)
		{
			_salir = true;
		}
		if(seleccion == Menu::I_Guardar)
		{
			((Application*)(SM))->saveCandyNapper();
			InterfazGraphics::getInstance()->visibilidadTextoCentral(true);
			InterfazGraphics::getInstance()->setTextoCentral1("       Guardado Correctamente");
			InterfazGraphics::getInstance()->setTextoCentral2("         Puedes Continuar");
		}
	}
}

void StatePause::decodeConsole() {
	Console* consola = _ig->getVentana()->getConsolePtr();

	if (consola->IsActive()) {
		if (consola->IsComplete()) {
			vector<string> comando = consola->GetCommandSplitted();

			if (comando.size() > 0) {
				//add-enemy x y z oso|melon|gengibre
				//kill-enemy id
				if (comando[0] == "add-enemy" && comando.size() == 5) {
					float x = atof(comando[1].c_str());
					float y = atof(comando[2].c_str());
					float z = atof(comando[3].c_str());
					string tipo = comando[4];

					if(tipo=="oso")
						CandyNapper::getInstancia()->getEm()->addEnemy(Vector3(x, y, z), Enemy::Oso)->Update();
					else if(tipo=="melon")
						CandyNapper::getInstancia()->getEm()->addEnemy(Vector3(x, y, z), Enemy::Melon)->Update();
					else if(tipo=="gengibre")
						CandyNapper::getInstancia()->getEm()->addEnemy(Vector3(x, y, z), Enemy::Gengibre)->Update();

				} else if (comando[0] == "kill-enemy" && comando.size() == 2) {
					if (comando[1] == "all") {
						CandyNapper::getInstancia()->getEm()->deleteType(GameEntity::Enemigo);
					} else {
						int id = atoi(comando[1].c_str());
						CandyNapper::getInstancia()->getEm()->deleteEntity(GameEntity::Enemigo, id);
					}
				} else if (comando[0] == "mv") {
					if (comando.size() == 2) {
						if (comando[1] == "center") {
							CandyNapper::getInstancia()->getEm()->getPlayer()->setPosicion(Vector3(0, 0, 0));
							//c_Owner->getEm()->getPlayer()->Update();
						}
					}
				} else if (comando[0] == "randEnemies"){
					if (comando.size() == 2) {
						int num = atoi(comando[1].c_str());
						for(int i =0; i< num; i++){
							int x = rand()%200 -100;
							int y = rand()%200 -100;
							CandyNapper::getInstancia()->getEm()->addEnemy(Vector3(x, 0, y), Enemy::Oso)->Update();
						}
					}
				}
			}
		}
	}
}

} /* namespace candy */
