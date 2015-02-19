/*
 * StateChangeLevel.cpp
 *
 *  Created on: 17/05/2012
 *      Author: carrillo
 */

#include "StateChangeLevel.h"
#include "Application.h"
#include "Menu.h"

namespace candy {

StateChangeLevel::StateChangeLevel()
:State(StateMachineGame::ChangeLevel)
{


	firstime = true;
	continuar = false;
}

StateChangeLevel::~StateChangeLevel() {
}

void StateChangeLevel::Transition() {
	if (InterfazGraphics::getInstance()->getVentana()->isClosing() || Teclado::isPulsada(Teclado::Q)) {
			SM->ChangeState(StateMachineGame::Exit);
	}else if(continuar)
	{
		continuar = false;
		firstime = true;
		InterfazGraphics::getInstance()->visibilidadHUD(true);
		InterfazGraphics::getInstance()->visibilidadWorld(true);
		InterfazGraphics::getInstance()->visibilidadMenuCambioNivel(false);
		SM->ChangeState(StateMachineGame::Play);
	}
}

void StateChangeLevel::Execute() {
	owner = ((Application*)(SM));
	InterfazGraphics::getInstance()->getVentana()->Update();

	if(firstime)
	{
		cout << "[StateChangeLevel] Es la primera vez que entro en execute cambiar nivel" << endl;

		InterfazGraphics::getInstance()->visibilidadMenuCambioNivel(true);
		InterfazGraphics::getInstance()->visibilidadWorld(false);
		InterfazGraphics::getInstance()->visibilidadHUD(false);

		InterfazGraphics::getInstance()->Render();
		InterfazGraphics::getInstance()->getVentana()->Display();

		cout << "[StateChangeLevel] Obtengo a que nivel tengo que ir ahora" << endl;

		nextLevel = (string)CANDYROOT + "/resources/" + CandyNapper::getInstancia()->getNextLevel();
		CandyNapper::getInstancia()->setActualLevel(nextLevel);
		cout << "[StateChangeLevel] Siguente nivel: " << nextLevel << endl;
		cout << "[StateChangeLevel] Inicializo CandyNapper" << endl;
		CandyNapper::getInstancia()->Init();
		cout << "[StateChangeLevel] Cargo el nuevo mapa" << endl;
		if(owner == NULL){
			cout << "[StateChangeLevel.cpp] es null" << endl;
		}else{
			owner->LoadFromXML(nextLevel);
		}

		cout << "[StateChangeLevel] Configurado para el siguiente nivel" << endl;
		firstime = false;

	}
	else
	{
		int seleccion = InterfazGraphics::getInstance()->seleccionMenuCambioNivel();

		if(seleccion == Menu::CL_Guardar)
		{
			InterfazGraphics::getInstance()->visibilidadTextoCentral(true);
			InterfazGraphics::getInstance()->setTextoCentral1("       Guardado Correctamente");
			InterfazGraphics::getInstance()->setTextoCentral2("         Puedes Continuar");
			owner->saveCandyNapper();
		}
		else if(seleccion == Menu::CL_Continuar)
		{
			continuar = true;
		}


	}
	InterfazGraphics::getInstance()->Render();
	InterfazGraphics::getInstance()->getVentana()->Display();
}

} /* namespace candy */
