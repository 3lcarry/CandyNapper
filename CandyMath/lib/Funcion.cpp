/*
 * Funcion.cpp
 *
 *  Created on: 22/03/2012
 *      Author: kaseyo
 */

#include "Funcion.h"
namespace candy {


Funcion::Funcion() {
	_tipo = Igual;
	_resultado = Rational::Cero;
}

Funcion::Funcion(string funcion) {
	read(funcion);
}

Funcion::Funcion(const list<Termino>& terminos){
	_funcion = terminos;
	_resultado = Rational::Cero;
	_tipo = Igual;
}

Funcion::~Funcion() {
	_funcion.clear();
	_resultado = Rational::Cero;
	_tipo = Nada;
}

Funcion::Funcion(const Funcion& func){
	copiarDesde(func);
}

Funcion&
Funcion::operator =(const Funcion& func){
	if(this != &func){
		this->~Funcion();
		copiarDesde(func);
	}

	return *this;
}

ostream&
operator<<(ostream& os, const Funcion& func){
	list<Termino>::const_iterator it;
	list<Termino>::const_iterator end = func._funcion.end();

	for(it = func._funcion.begin(); it != end; it++){
		os << *it << " ";
	}

	//os << " = " << func._resultado;
	switch(func._tipo){
	case Funcion::Igual:
		os << " = " << func._resultado;
		break;

	case Funcion::MayorQue:
		os << " > " << func._resultado;
		break;

	case Funcion::MenorQue:
		os << " < " << func._resultado;
		break;

	case Funcion::MayorIgual:
		os << " >= " << func._resultado;
		break;

	case Funcion::MenorIgual:
		os << " <= " << func._resultado;
		break;

	case Funcion::Nada:

		break;
	}

	return os;
}

void
Funcion::copiarDesde(const Funcion& func){
	_funcion = func._funcion;
	_resultado = func._resultado;
	_tipo = func._tipo;
}

void
Funcion::read(string funcion){
	string termino = "";
	string resultado = "";
	int tipo = -1;
	bool leidoTerm = false;

	for(unsigned i = 0; i <= funcion.size(); i++){
		if(leidoTerm){
			leidoTerm = false;
			if(termino != ""){
				//Si hay leido algun termino
				_funcion.push_back(Termino(termino));
				termino = "";
			}
		}

		if(i == funcion.size()){
			if(termino != ""){
				//Si hay leido algun termino
				_funcion.push_back(Termino(termino));
				termino = "";
			}
		}else if(funcion[i] == '+' || funcion[i] == '-'){
			//Este lo tengo que dejar aqui, por que justo despues sobrescribe el termino
			if(termino != ""){
				//Si hay leido algun termino
				_funcion.push_back(Termino(termino));
				termino = "";
			}
			//Empiezo a leer uno
			if(tipo != -1){
				resultado = funcion[i];
			}else{
				termino = funcion[i];
			}
		}else if(funcion[i] == '='){
			if(tipo == MenorQue){
				tipo = MenorIgual;
			}else if(tipo == MayorQue){
				tipo = MayorIgual;
			}else{
				tipo = Igual;

				leidoTerm = true;
			}
		}else if(funcion[i] == '<'){
			tipo = MenorQue;
			leidoTerm = true;
		}else if(funcion[i] == '>'){
			tipo = MayorQue;
			leidoTerm = true;
		}else if(funcion[i] >= '0' && funcion[i] <= '9'){
			if(tipo != -1){
				//Ya he leido el simbolo
				resultado += funcion[i];
			}else{
				termino += funcion[i];
			}
		}else if(funcion[i] == 'X'){
			termino += funcion[i];
		}
	}

	if(tipo != -1){
		_tipo = TipoFuncion(tipo);
	}else{
		_tipo = Nada;
	}

	_resultado = atof(resultado.c_str());
}

Rational
Funcion::getResultado(vector<int> indices, vector<Rational> valores) const
{
	Rational resultado = Rational::Cero;

	list<Termino>::const_iterator it;

	for(it = _funcion.begin(); it != _funcion.end(); it++){
		int varActual = it->getVarIndex();

		bool encontrado = false;
		int indEnc;
		for(int i = 0; i < indices.size() && !encontrado; i++){
			if(varActual == indices[i]){
				encontrado = true;
				indEnc = i;
			}
		}

		//CALCULAMOS EL RESULTADO SUMANDO EL VALOR DEL TERMINO
		if(encontrado){
			resultado += it->getCoef()*valores[indEnc];
		}
	}

	return resultado;
}

vector<string>
Funcion::split(string cadena, char separador){
	//Esto habra que meterlo en una funcion "split" de una futura libreria candy-utilities o algo asi..., al menos
	//si lo usamos en algun sitio mas
	vector<string> troceado;
	string trozo = "";

	for(unsigned i = 0; i <= cadena.size(); i++){
		if(i == cadena.size() || cadena[i] == separador){
			troceado.push_back(trozo);
			trozo = "";
		}else{
			trozo += cadena[i];
		}
	}

	return troceado;
}

list<int>
Funcion::getVariables() const{
	list<int> resultado;
	list<int>::iterator it;

	list<Termino>::const_iterator it_term;
	for(it_term = _funcion.begin(); it_term != _funcion.end(); it_term++){
		//it = resultado.begin();
		int variable = it_term->getVarIndex();
/*
		while((*it) < variable && it != resultado.end()){
			it++;
		}

		if((*it) > variable){
			//Insertamos
			resultado.insert(it, variable);
		}
		*/
		resultado.push_back(variable);
	}

	resultado.sort();

	return resultado;
}

Funcion
Funcion::operator -() const{
	Funcion res;

	switch(_tipo){
	case MayorQue:
		res._tipo = MenorQue;
		break;
	case MayorIgual:
		res._tipo = MenorIgual;
		break;
	case MenorQue:
		res._tipo = MayorQue;
		break;
	case MenorIgual:
		res._tipo = MayorIgual;
		break;
	default:
		res._tipo = _tipo;
		break;
	}

	res._resultado = -_resultado;
	list<Termino>::const_iterator it;

	for(it = _funcion.begin(); it != _funcion.end(); it++){
		res._funcion.push_back(-(*it));
	}


	return res;
}

Funcion::TipoFuncion
Funcion::getTipo() const{
	return _tipo;
}


void
Funcion::setTipo(Funcion::TipoFuncion tipo){
	_tipo = tipo;
}

void
Funcion::addTermino(const Termino& ter){
	_funcion.push_back(ter);
}

Rational
Funcion::getCoeficiente(int var) const{
	Rational coef(0);

	list<Termino>::const_iterator it;

	for(it = _funcion.begin(); it!= _funcion.end(); it++)
	{
		if(it->getVarIndex() == var)
		{
			coef = it->getCoef();
			break;
		}
	}

	return coef;
}

Rational
Funcion::getResultado() const{
	return _resultado;
}

void
Funcion::setResultado(Rational r){
	_resultado = r;
}

} /* namespace candy */
