/*
 * SimplexHeap.cpp
 *
 *  Created on: 17/05/2012
 *      Author: kaseyo
 */

#include "SimplexHeap.h"

namespace candy {
// ## SimplexHeap

SimplexHeap::SimplexHeap(){
	make_heap(_heap.begin(), _heap.end(), &Ordenar);
}

SimplexHeap::~SimplexHeap(){
	_heap.clear();
}

void
SimplexHeap::Push(SimplexNode nodo){
	_heap.push_back(nodo);
	push_heap(_heap.begin(), _heap.end(), &Ordenar);
}

SimplexNode
SimplexHeap::Pop(){
	SimplexNode n;
	if(!_heap.empty()){
		n = _heap.front();
		pop_heap(_heap.begin(), _heap.end(), &Ordenar);
		_heap.pop_back();
	}

	return n;
}

bool
SimplexHeap::Vacio(){
	return _heap.empty();
}

bool
SimplexHeap::Ordenar(SimplexNode a, SimplexNode b){
	bool mejor = false;

	if(a._prob.getTipoProblema() == Problema::MAX){
		mejor = a._optimo > b._optimo;
	}else if(a._prob.getTipoProblema() == Problema::MIN){
		mejor = a._optimo > b._optimo;
	}

	return mejor;
}

// ## SimplexNode
ostream&
operator<<(ostream& os, const SimplexNode& sn){
	os << "[SimplexHeap.cpp] Problema: " << endl;
	os << sn._prob;
	os << "[SimplexHeap.cpp] Soluciones: " << endl;
	for(int i = 0; i < sn._variables.size(); i++){
		os <<"Var: " << i+1 << " = " << sn._variables[i] << " ; ";
	}
	os << endl;
	os << "[SimplexHeap.cpp] Optimo: " << endl;
	os << sn._optimo << endl;
	os << "[SimplexHeap.cpp] Profundidad: " << endl;
	os << sn._profundidad << endl;

	return os;
}

SimplexNode::SimplexNode(){
	_optimo = Rational::Cero;
	_profundidad = 0;
}

SimplexNode::SimplexNode(const vector<Rational>& variables, const Rational& optimo, int profundidad, const Problema& prob){
	_optimo = optimo;
	_variables = variables;
	_profundidad = profundidad;
	_prob = prob;
}

SimplexNode::~SimplexNode(){
	_variables.clear();
	_optimo = Rational::Cero;
	_profundidad = 0;
}

SimplexNode::SimplexNode(const SimplexNode& node){
	copiarDesde(node);
}

SimplexNode&
SimplexNode::operator =(const SimplexNode& node){
	if(&node != this){
		_variables.clear();
		copiarDesde(node);
	}

	return *this;
}

void
SimplexNode::copiarDesde(const SimplexNode& node){
	_optimo = node._optimo;
	_variables = node._variables;
	_profundidad = node._profundidad;
	_prob = node._prob;
}

} /* namespace candy */
