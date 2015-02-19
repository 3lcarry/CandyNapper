/*
 * Termino.cpp
 *
 *  Created on: 22/03/2012
 *      Author: kaseyo
 */

#include "Termino.h"

#include <cmath>
#include <cstdlib>


namespace candy {

ostream &
operator <<(ostream & os, const Termino & ter) {
	if(ter._coeficiente > Rational::Cero){
		os << "+";
	}
	os << ter._coeficiente << "*X" << ter._variable;

	return os;
}

Termino::Termino(int coef, int var) {
	_coeficiente = coef;
	_variable = var;
}

Termino::Termino(string termino){
	string coef = "";
	string var = "";
	bool acabadoNum = false;

	for(int i = 0; i < termino.size(); i++){
		if(!acabadoNum && ((termino[i] >= '0' && termino[i] <= '9') || termino[i] == '+' || termino[i] == '-')){
			coef += termino[i];
		}else if(termino[i]=='X'){
			acabadoNum = true;
		}else if(acabadoNum){
			var += termino[i];
		}
	}

	//cout << "[Termino.cpp] Desde " << termino << "(" << termino.length() << ")" << " - Coef = " << coef << "(" << coef.length() << ");Var = " << var << "(" << var.length() << ")";

	if(coef.length() > 0){
		_coeficiente = atof(coef.c_str());
	}else{
		_coeficiente = 1;
	}

	if(var.length() > 0){
		_variable = atoi(var.c_str());
	}else{
		_variable = 0;
	}
}

Termino::~Termino() {
	_coeficiente = -1;
	_variable = -1;
}

Termino::Termino(const Termino & ter) {
	_coeficiente = ter._coeficiente;
	_variable = ter._variable;
}

Termino &
Termino::operator =(const Termino & ter) {
	_coeficiente = ter._coeficiente;
	_variable = ter._variable;

	return *this;
}

Rational
Termino::getCoef() const{
	return _coeficiente;
}

int
Termino::getVarIndex() const{
	return _variable;
}

Termino
Termino::operator -() const{
	Termino res(*this);
	res._coeficiente = -_coeficiente;
	return res;
}

} /* namespace candy */
