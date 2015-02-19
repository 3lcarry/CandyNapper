#include "State.h"
#include "StateMachine.h"

namespace candy{

State::State(){
	ID = -1;
	SM = NULL;
}

State::State(int id){
	ID = id;
	SM = NULL;
}

State::State(int id, StateMachine* sm){
	ID = id;
	SM = sm;
}

/**
* Destructor
*/
State::~State(){

}

/**
* Añade la ID al estado
* @param ID del estado
*/
void
State::setID(int id){
	ID = id;
}

/**
* Devuelve el ID del estado
* @return ID del estado
*/
int
State::getID(){
	return ID;
}

/**
* Indica el propiterario del estado
* @param puntero a la máquina de estados a la que pertenece el estado
*/
void
State::setStateMachine(StateMachine *sm){
	SM = sm;
}

/**
* Devuelve a que máquina de estados pertene este estado
* @return ID de la máquina de estados
*/
int
State::getStateMachine(){
	return SM->getID();
}

/**
* Se obtiene un estado a partir de su ID
* @param ID del estado a buscar
* @param puntero al estado que se buscaba
*/
State*
State::getStateByID(int id){

	//vector<State<T>*> states;
	//states = SM->getStates();

	//vector<State<T>*>::iterator i;

	//for(i=states.begin(); i != states.end(); i++){
	//	if(i->getID() == id)
	//		return i;
	//}
	for(unsigned i =0; i< SM->getStates().size();i++){
		if(SM->getStates()[i]->getID() == id){
			return SM->getStates()[i];
			break;
		}
	}
	return NULL;
}

/**
* Sirbe para cambiar de estado
* @param ID del estado al que se quiere cambiar
* @return boleano que indica si el cambio a sido correcto
*/
bool
State::ChangeTo(int id){
	return  SM->ChangeState(id);
}

}
