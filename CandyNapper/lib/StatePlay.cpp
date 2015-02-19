/*
 * PlayState.cpp
 *
 *  Created on: Nov 23, 2011
 *      Author: carrillo
 */

#include "StatePlay.h"

#include "InterfazGraphics.h"
#include "InterfazPhysics.h"
#include "EntityManager.h"
#include "Application.h"

#include "Teclado.h"


#include <sstream>
using namespace std;

namespace candy {

StatePlay::StatePlay()
	:State(StateMachineGame::Play)
{
	//ID = StateMachineGame::Play;
	//SM = NULL;
	_if = InterfazPhysics::getInstance();
	_ig = InterfazGraphics::getInstance();
	_idSoundBird = InterfazMusic::getInstancia()->AddSonido(InterfazMusic::Bird);
	_lastTimeSound = 0;
	if(Timer::getTimeElapsed()%2 == 0)
		srand(Timer::getTimeElapsed()*(-27));
	else
		srand(Timer::getTimeElapsed()*(-13));
}

StatePlay::~StatePlay() {

}

void StatePlay::Transition() {
	Application *owner = ((Application*)(SM));
	if(_ig->getVentana()->isClosing() == true ){
		SM->ChangeState(StateMachineGame::Exit);
	}else if(_pausa){
		_ig->visibilidadMenuIngame(true);
		_ig->visibilidadMenuFinish(false);
		_ig->getVentana()->ShowMouse(true);
		_ig->visibilidadMenuWin(false);
		SM->ChangeState(StateMachineGame::Pause);
	}

	else if(CandyNapper::getInstancia()->ChangeLevel())
	{
		cout << "[StatePlay.cpp] Voy a cambiar de nivel" << endl;
		_ig->getVentana()->ShowMouse(true);
		_ig->visibilidadMenuCambioNivel(true);
		_ig->visibilidadWorld(false);
		_ig->visibilidadHUD(false);
		_ig->visibilidadMenuFinish(false);
		_ig->visibilidadMenuWin(false);
		SM->ChangeState(StateMachineGame::ChangeLevel);

	}
	else if(CandyNapper::getInstancia()->getEm()->isGameOver())
	{
		_ig->getVentana()->ShowMouse(true);
		_ig->visibilidadMenuFinish(true);
		_ig->visibilidadMenuCambioNivel(false);
		_ig->visibilidadWorld(false);
		_ig->visibilidadHUD(false);
		_ig->visibilidadMenuIngame(false);
		_ig->visibilidadMenuWin(false);
		SM->ChangeState(StateMachineGame::GameOver);
		InterfazMusic::getInstancia()->desactivarMusicaFondo();
		InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Menu);
	}
	else if(CandyNapper::getInstancia()->isGameComplete()){
		_ig->getVentana()->ShowMouse(true);
		_ig->visibilidadMenuFinish(false);
		_ig->visibilidadMenuCambioNivel(false);
		_ig->visibilidadWorld(false);
		_ig->visibilidadHUD(false);
		_ig->visibilidadMenuIngame(false);
		_ig->visibilidadMenuWin(true);
		SM->ChangeState(StateMachineGame::Win);
		InterfazMusic::getInstancia()->desactivarMusicaFondo();
		InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Menu);
	}

}

void StatePlay::Execute() {
	_pausa = false;

	//Actualizamos eventos de ventana en motor grafico
	_ig->getVentana()->Update();

	float fps = _ig->getVentana()->getFramesPerSecond();

	//Actualizamos Fisica
	_if->Update(1.0/fps);

	// Actualizamos los componentes de todas las entidades
	CandyNapper::getInstancia()->getEm()->Update();

	//Renderizamos el motor grafico
	_ig->Render();

	//Miramos si estamos en pause
	if(_teclado.isPulsada(Teclado::P))
	{
		_pausa = true;
	}

	//Mostramos el resultado del renderizado
	_ig->getVentana()->Display();

	bool play = false;


	if(Timer::getTimeElapsed() - _lastTimeSound > 0){
		_lastTimeSound = Timer::getTimeElapsed() + rand()%60000;
		play = true;
	}

	if(play && !InterfazMusic::getInstancia()->getMusicEngine()->S_IsPlaying(_idSoundBird)){
		InterfazMusic::getInstancia()->getMusicEngine()->S_Play(_idSoundBird);
		play = false;
	}

}


} /* namespace candy */
