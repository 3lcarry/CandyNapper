/*
 * Problema.cpp
 *
 *  Created on: 29/03/2012
 *      Author: kaseyo
 */

#include "Problema.h"
#include "Common.h"
#include <cmath>
#include <list>

namespace candy {

Problema::Problema() {

}

ostream &
operator <<(ostream & os, const Problema & prob){
	if(prob._tipo == Problema::MAX){
		os << "MAX ";
	}else if(prob._tipo == Problema::MIN){
		os << "MIN ";
	}else{
		os << "-MIN ";
	}

	os << prob._funcObjetivo << endl;

	for(unsigned i = 0; i < prob._restricciones.size(); i++){
		os << prob._restricciones[i] << endl;
	}

	return os;
}

Problema::~Problema(){
	_restricciones.clear();
	_funcObjetivo = Funcion();
	_tipo = MIN;
	_artificiales.clear();
}

Problema::Problema(vector<string> problema){
	read(problema);
}

Problema::Problema(const Problema & prob){
	copiarDesde(prob);
}

Problema &
Problema::operator =(const Problema & prob){
	if(this != &prob){
		copiarDesde(prob);
	}

	return *this;
}

void Problema::read(vector<string> problema){
	for(unsigned i = 0; i < problema.size(); i++){
		if(i == 0){
			//Mini bucle para leer el MAX/MIN
			string tipo = "";
			bool leido = false;
			unsigned j;

			for(j = 0; j < problema[i].size() && !leido; j++){
				if(problema[i][j] == ' '){
					leido = true;
				}else{
					tipo += problema[i][j];
				}
			}

			_funcObjetivo = Funcion(problema[i].substr(j));

			if(tipo == "MAX"){
				_tipo = MAX;
			}else{
				_tipo = MIN;
			}
		}else{
			_restricciones.push_back(Funcion(problema[i]));
		}
	}
}

list<int>
Problema::getVariables() const{
	list<int> variables;
	list<int> aux = _funcObjetivo.getVariables();

	//variables.merge(aux);
	variables = aux;

	for(unsigned i = 0; i < _restricciones.size(); i++){
		aux = _restricciones[i].getVariables();

		variables = CandyMath::Merge(variables, aux);
	}

	return variables;
}

Matrix
Problema::ObtenerColumna(int col) const
{
	int maxCol = getVariables().size();
	Matrix res(_restricciones.size() ,1);

	if(col <= maxCol)
	{
		for(int i=0; i< _restricciones.size(); i++)
		{
			res(i,0) = _restricciones[i].getCoeficiente(col);
		}
	}
	return res;
}

Rational Problema::ObtenerCoeficienteFuncion(int col) const
{
	return _funcObjetivo.getCoeficiente(col);
}

vector<int> Problema::ObtenerNoBasicas(vector<int> basicas) const
{
	list<int> variables = getVariables();

	for(int i=0; i<basicas.size(); i++)
	{
		variables.remove(basicas[i]);
	}

	vector<int> res;

	list<int>::iterator it;
	for(it = variables.begin(); it != variables.end(); it++)
	{
		res.push_back(*it);
	}

	return res;
}

void
Problema::copiarDesde(const Problema& p){
	_funcObjetivo = p._funcObjetivo;
	_restricciones = p._restricciones;
	_tipo = p._tipo;
	_artificiales = p._artificiales;
}

void
Problema::addRestriccion(const Funcion& f){
	_restricciones.push_back(f);
}

void
Problema::setObjetivo(TipoProblema tipo){
	_tipo = tipo;
}

void
Problema::setFuncObjetivo(const Funcion& f){
	_funcObjetivo = f;
}

void
Problema::Normalizar(){
	if(_tipo == Problema::MAX){
		_tipo = Problema::_MIN;
		_funcObjetivo = -_funcObjetivo;
	}

	int num_var = this->getVariables().size();

	for(unsigned i = 0; i < _restricciones.size(); i++){
		if(_restricciones[i].getTipo() == Funcion::MenorQue || _restricciones[i].getTipo() == Funcion::MenorIgual){
			Termino ter(1, ++num_var);
			_restricciones[i].addTermino(ter);
		}else if(_restricciones[i].getTipo() == Funcion::MayorQue || _restricciones[i].getTipo() == Funcion::MayorIgual){
			Termino ter(-1, ++num_var);
			_restricciones[i].addTermino(ter);
		}

		_restricciones[i].setTipo(Funcion::Igual);
	}
}

void
Problema::NormalizarDual(){
	if(_tipo == Problema::MAX){
		_tipo = Problema::_MIN;
		_funcObjetivo = -_funcObjetivo;
	}

	int num_var = this->getVariables().size();

	for(unsigned i = 0; i < _restricciones.size(); i++){
		if(_restricciones[i].getTipo() == Funcion::MenorQue || _restricciones[i].getTipo() == Funcion::MenorIgual){
			Termino ter(1, ++num_var);
			_restricciones[i].addTermino(ter);
		}else if(_restricciones[i].getTipo() == Funcion::MayorQue || _restricciones[i].getTipo() == Funcion::MayorIgual){
			Termino ter(-1, ++num_var);
			_restricciones[i].addTermino(ter);

			_restricciones[i] = -(_restricciones[i]);
		}

		_restricciones[i].setTipo(Funcion::Igual);
	}
}

Matrix
Problema::ObtenerBase(){
	int dim = CandyMath::Min(_restricciones.size(), getVariables().size());
	Matrix res(dim);

	vector<int> aux = ObtenerBasicas();

	for(int i = 0; i < aux.size(); i++){
		int var = aux[i];
		for(int j = 0; j < dim; j++){
			res(j, i) = _restricciones[j].getCoeficiente(var);
		}
	}


	return res;
}

vector<int>
Problema::ObtenerBasicas(){
	int dim = CandyMath::Min(_restricciones.size(), getVariables().size());

	//Buscamos si hay algun elem con =1 y todos los de alrededor =0
	vector<int> base = getIdentidadBase();

	vector<int> aux(dim);
	int numBasicas = 0;

	for(int i = 0; i < base.size() && numBasicas < dim; i++){
		if(base[i] != -1){
			//Lo a–ado al res
			aux[numBasicas] = i + 1;
			numBasicas++;
		}
	}

	if(numBasicas < dim){

		//Si aun tenemos que a–adir variables basicas, buscamos una que no este marcada en el vector de la base
		for(int i = 0; i < base.size() && numBasicas < dim; i++){
			if(base[i] == -1){
				//Lo a–ado al res
				aux[numBasicas] = i + 1;
				numBasicas++;
			}
		}
	}


	return aux;
}

void
Problema::addArtificiales() {
	vector<int> base = getIdentidadBase();
	list<int> var = getVariables();
	int numVariables = var.size();
	int dim = CandyMath::Min(_restricciones.size(), numVariables);

	int cont = 0;
	for(int i = 0; i < base.size() && cont < dim; i++){
		if(base[i] != -1){
			cont++;
		}
	}

	if(cont < dim){
		//Anyadimos artificiales
		int nArtif = dim - cont;
		int iActual = numVariables + 1;

		for(int i = 0; i < nArtif; i++){
			//Busco una restriccion donde necesite meter un "(1, 0, 0)"
			bool found = false;
			int res = 0;
			for(int j = 0; j < _restricciones.size() && !found; j++){
				//Busco entre base, a ver si 'j' no existe
				bool existe = false;
				for(int k = 0; k < base.size() && !existe; k++){
					if(base[k] == j){
						existe = true;
					}
				}

				if(!existe){
					found = true;
					res = j;
				}
			}

			if(found){
				_restricciones[res].addTermino(Termino(1, iActual));
				_funcObjetivo.addTermino(Termino(CandyMath::INFINITO, iActual));
				_artificiales.push_back(iActual);
				base.push_back(res);

				iActual++;
			}
		}

		//_xa = iActual;
	}
}

vector<int>
Problema::getIdentidadBase() const {
	list<int> variables = getVariables();
	int numVar = variables.size();
	int dim = CandyMath::Min(_restricciones.size(), numVar);

	//Buscamos si hay algun elem con =1 y todos los de alrededor =0
	vector<int> base(numVar, -1);
	int i, j, k;
	bool cero = true;
	bool encontrada = false;
	for (i = 0; i < dim; i++) {
		encontrada = false;
		for (j = 0; j < numVar && !encontrada; j++){
			if (_restricciones[i].getCoeficiente(j + 1) == Rational::Uno) {
				cero = true;
				for (k = 0; k < dim && cero; k++){
					if (k != i && _restricciones[k].getCoeficiente(j + 1) != Rational::Cero){
						cero = false;
					}
				}
				if (cero){
					base[j] = i;
				}
			}

		}
	}

	return base;
}

Matrix
Problema::ObtenerD() const{
	int dim = CandyMath::Min(_restricciones.size(), getVariables().size());
	Matrix d(dim, 1);

	for(int i = 0; i < dim; i++){
		d(i, 0) = _restricciones[i].getResultado();
	}

	return d;
}

Funcion
Problema::getFuncObjetivo() const {
	return _funcObjetivo;
}

Problema::TipoProblema
Problema::getTipoProblema() const {
	return _tipo;
}

vector<int>
Problema::getArtificiales() const {
	return _artificiales;
}

bool
Problema::hayNegEnD() const {
	bool neg = false;

	for(int i = 0; i < 0 && !neg; i++){
		if(_restricciones[i].getResultado() < Rational::Cero){
			neg = true;
		}
	}

	return neg;
}

} /* namespace candy */
