#include "StateMachine.h"
#include "State.h"

namespace candy {

StateMachine::StateMachine(){
	ID = -1;
	CurrentState = NULL;
	InitialState = NULL;
}


StateMachine::StateMachine(int id, vector<State*> states, State* cs, State* is){
	ID = id;
	States = states;
	CurrentState = cs;
	InitialState = is;
}

StateMachine::~StateMachine(){

	for(unsigned i = 0; i < States.size(); i++){
		delete States[i];
		States[i] = NULL;
	}
/*
	if(CurrentState != NULL){
		delete CurrentState;
	}

	if(InitialState != NULL){
		delete InitialState;
	}
*/
}

int
StateMachine::getID(){
	return ID;
}

State*
StateMachine::getCurrentState(){
	return CurrentState;
}

State*
StateMachine::getInitialState(){
	return InitialState;
}

vector<State*>
StateMachine::getStates(){
	return States;
}

void
StateMachine::setID(int id){
	ID = id;
}

void
StateMachine::setCurrentState(State* s){
	CurrentState = s;
}

void
StateMachine::setInitialState(State* s){
	InitialState = s;
	CurrentState = s;
}

void
StateMachine::setStates(vector<State*> s){
	States = s;
}

bool
StateMachine::AddState(State* s){
	int size = States.size();

	for(int i =0; i < size; i++){
		if(States[i]->getID() == s->getID())
			return false;
	}

	s->setStateMachine(this);
	States.push_back(s);
	return true;
}

bool
StateMachine::ChangeState(int id){

		bool changed = false;
		int size = States.size();

		for(int i=0; i<size;i++){
			if(States[i]->getID() == id){
				CurrentState = States[i];
				changed = true;
				break;
			}
		}

		return changed;
}

void
StateMachine::Update(){
	if(CurrentState != NULL){
		CurrentState->Execute();
		CurrentState->Transition();
	}
}

}
