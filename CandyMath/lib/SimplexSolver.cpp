/*
 * SimplexSolver.cpp
 *
 *  Created on: 22/03/2012
 *      Author: kaseyo
 */

#include "SimplexSolver.h"
#include "Common.h"

#include <cmath>

namespace candy {

SimplexSolver::SimplexSolver() {
	// TODO Auto-generated constructor stub

}

SimplexSolver::~SimplexSolver() {
	variablesUsadas.clear();
}

Rational
SimplexSolver::IntSimplexSolve(const Problema& p){
	SimplexHeap nodosVivos;
	vector<Rational> solTemporales;
	vector<SimplexNode> nodosExpandidos;
	vector<Rational> mejorSolucion;
	Rational mejorOptimo(0);
	Rational optimoInit(0);
	int numNodos = 0; //Init en 1 x el inicial
	Problema probAux = p;
	bool fin = false;

	//prob = p;

	vector<int> varObjetivo;
	list<int> listaAux = p.getFuncObjetivo().getVariables();
	list<int>::iterator it;
	for(it = listaAux.begin(); it != listaAux.end(); it++){
		varObjetivo.push_back(*it);
	}

	//Añado el nodo inicial
	optimoInit = DualSimplexSolve(p);
	solTemporales = getSolTemporales(varObjetivo);
	SimplexNode nodoInit(solTemporales, optimoInit, 0, p);
	if(EsSolucion(nodoInit)){
		mejorOptimo = nodoInit._optimo;
		mejorSolucion = nodoInit._variables;

		fin = true;
	}
	nodosVivos.Push(nodoInit);

	while(!nodosVivos.Vacio() && !fin){
		SimplexNode nodoActual = nodosVivos.Pop();

		//solEntera = true;
		//nodosExpandidos = Expandir(nodoAux);
		nodosExpandidos = Expandir(nodoActual);

		//cout << "[SimplexSolver.cpp] Analizamos los nodos expandidos: " << endl;
		for(int i = 0; i < (int)nodosExpandidos.size(); i++){
			//Calculamos el valor de cota
			nodosExpandidos[i]._optimo = DualSimplexSolve(nodosExpandidos[i]._prob);
			//nodosExpandidos[i]._prob = prob; //Le asignamos el problema ya normalizado
			nodosExpandidos[i]._variables = getSolTemporales(varObjetivo);

			/*
			cout << "[SimplexSolver.cpp] Nodo expandido " << i << " del nodo del arbol numero " << numNodos << endl;
			cout << nodosExpandidos[i] << endl;
			*/
			//Factible -> this->estado == SolEncontrada
			//Aceptable -> aun no controlamos la cota
			//EsSolucion -> la solucion es entera

			if(estado == SolEncontrada && Aceptable(nodosExpandidos[i], mejorOptimo, mejorSolucion)){
				if(EsSolucion(nodosExpandidos[i])){
					numNodos++;
					//Actualizamos la cota
					//cout << "[SimplexSolver.cpp] TENEMOS UNA SOLUCION ########### " << endl;
					if(nodosExpandidos[i]._optimo == optimoInit){
						//Hemos encontrado el mejor optimo posible, terminamos
						fin = true;
						mejorSolucion = nodosExpandidos[i]._variables;
						mejorOptimo = nodosExpandidos[i]._optimo;
					}else{
						if(mejorSolucion.size() == 0){
							//Es la primera
							mejorSolucion = nodosExpandidos[i]._variables;
							mejorOptimo = nodosExpandidos[i]._optimo;
						}

						if(prob.getTipoProblema() == Problema::_MIN || prob.getTipoProblema() == Problema::MAX){
							//El objetivo es maximizar
							if(mejorOptimo < nodosExpandidos[i]._optimo){
								mejorOptimo = nodosExpandidos[i]._optimo;
								mejorSolucion = nodosExpandidos[i]._variables;
							}
						}else if(prob.getTipoProblema() == Problema::MIN){
							//El objetivo es minimizar
							if(mejorOptimo > nodosExpandidos[i]._optimo){
								mejorOptimo = nodosExpandidos[i]._optimo;
								mejorSolucion = nodosExpandidos[i]._variables;
							}
						}
					}
				}else{
					numNodos++;
					//Si aun no hemos acabado, lo a–adimos a la lista de nodos_vivos
					//cout << "[SimplexSolver.cpp] AUN NO ES SOLUCION, VA AL HEAP ##########" << endl;
					nodosVivos.Push(nodosExpandidos[i]);
				}
			}else{
				numNodos++;
				//Podamos por que no es factible o aceptable
				//cout << "[SimplexSolver.cpp] Estado del solver: " << estado << endl;
				//cout << "[SimplexSolver.cpp] PODAMOS PORQUE NO ES FACTIBLE ##########" << endl;
			}
		}
		//cout << endl;
	}

	if(mejorSolucion.size() > 0){
		estado = SolEncontrada;
	}

	optimo = mejorOptimo;
	soluciones = mejorSolucion;
	/*
	cout << "[SimplexSolver.cpp] FINAL ############## " << endl;
	cout << "[SimplexSolver.cpp] Optimos: " << endl;
	for(int i = 0; i < mejorSolucion.size(); i++){
		cout << "Var: " << i+1 << " = " << mejorSolucion[i] << " ";
	}
	cout << endl;
	cout << "[SimplexSolver.cpp] Numero de nodos totales: "<< numNodos << endl;
	*/
	return optimo;
}

Rational
SimplexSolver::DualSimplexSolve(const Problema& p){
	prob = p;
	//Rational optimo(0);

	prob.NormalizarDual();

	base = prob.ObtenerBase();
	baseInv = base.Inversa();
	variablesUsadas = prob.ObtenerBasicas();

	Matrix dBarra;
	int varEntra = 0, varSale = -1;

	vector<int> varObjetivo;
	list<int> listaAux = p.getFuncObjetivo().getVariables();
	list<int>::iterator it;
	for(it = listaAux.begin(); it != listaAux.end(); it++){
		varObjetivo.push_back(*it);
	}

	//Buscamos que todos los zjcj sean < 0
	checkRestriccionArtificial();

	bool solved = false;
	bool notSolution = false;
	//Pasamos a solucionarlo
	while(!solved && !notSolution){
		baseInv = base.Inversa();

		varSale = getVariableSalidaDual();

		if(varSale != -1){
			varEntra = getVariableEntradaDual(varSale);

			if(varEntra != -1){
				//Change de basicas
				cambiarBase(varSale, varEntra);
			}else{
				//Imposible
				notSolution = true;
				estado = SolNoExiste;
			}
		}else{
			//Optimo
			solved = true;
			estado = SolEncontrada;
		}

		//solved = true;
	}

	if(solved){
		optimo = getOptimo();
		soluciones = getSolTemporales(varObjetivo);
		//cout << "[SimplexSolver.cpp] El resultado es " << optimo << endl;
	}else{
		optimo = Rational::Cero;
	}

	return optimo;
}

Rational
SimplexSolver::PenalizacionesSolve(const Problema& p){
	Rational res(0);

	prob = p;
	prob.Normalizar();
	prob.addArtificiales();
	res = SimplexSolve(prob);

	vector<int> varObjetivo;
	list<int> listaAux = p.getFuncObjetivo().getVariables();
	list<int>::iterator it;
	for(it = listaAux.begin(); it != listaAux.end(); it++){
		varObjetivo.push_back(*it);
	}

	int xa = 0;
	vector<int> artif = prob.getArtificiales();
	for(unsigned i = 0; i < variablesUsadas.size(); i++){
		bool encontrado = false;
		for(unsigned j = 0; j < artif.size() && !encontrado; j++){
			if(artif[j] == variablesUsadas[i]){
				encontrado = true;
				xa++;
			}
		}
	}

	//El problema final se guarda en prob, o sea que podemos consultarlo
	if(estado == SolEncontrada){
		if(xa == 0){
			estado = SolEncontrada;
		}else{
			estado = SolNoExiste;
			//cout << "[SimplexSolver.cpp] Noexis1" << endl;
		}
	}else{
		if(xa == 0){
			estado = SolNoAcotada;
		}else{
			estado = SolNoExiste;
			//cout << "[SimplexSolver.cpp] Noexis2" << endl;
		}
	}

	if(estado != SolEncontrada){
		res = Rational::Cero;
		//cout << "[SimplexSolver.cpp] No hay solucion" << endl;
	}

	optimo = res;
	soluciones = getSolTemporales(varObjetivo);

	return res;
}

Rational
SimplexSolver::SimplexSolve(const Problema& prob2){
	Rational resultado;
	prob = prob2;
	prob.Normalizar();

	vector<int> varObjetivo;
	list<int> listaAux = prob2.getFuncObjetivo().getVariables();
	list<int>::iterator it;
	for(it = listaAux.begin(); it != listaAux.end(); it++){
		varObjetivo.push_back(*it);
	}

	//Inicializacion
	base = prob.ObtenerBase();
	//int columnas = base.getColumnas();
	/*
	variablesUsadas.clear();//(columnas);
	for(int i=0; i<columnas;i++)
	{
		variablesUsadas.push_back(i+1);
	}
	*/
	variablesUsadas = prob.ObtenerBasicas();

	bool solved = false;
	bool notSolution = false;

	int iteraciones = 0;

	while(!solved && !notSolution){
		baseInv = base.Inversa();

		int variableEntra = getVariableEntra();

		if(variableEntra != -1){
			//Tenemos los zjcj y hay uno mayor que cero vemos si tiene solucion para segir o salir
			int variableSalida = getVariableSalida(variableEntra);

			if(variableSalida != -1)
			{
				//Ya sabemos que indice sale
				//Cambiamos la base
				cambiarBase(variableSalida, variableEntra);

			}else{
				//No hay solucion ver que hacer
				notSolution = true;
				estado = SolNoAcotada;
			}
		}else{
			//Ya tenemos la solucion
			solved = true;
			estado = SolEncontrada;
		}
		iteraciones++;
	}

	if(solved)
	{
		//En la ultima it no se recalcula (se sale antes)
		//baseInv = base.Inversa();
		resultado = getOptimo();
		soluciones = getSolTemporales(varObjetivo);

		//cout << "[SimplexSolver.cpp] El resultado es " << resultado << endl;
	}
	else if(notSolution)
	{
		//cout << "[SimplexSolver.cpp] El problema no tiene solucion mediante Simplex" << endl;
	}

	optimo = resultado;

	return resultado;
}

void
SimplexSolver::cambiarBase(int variableSale, int variableEntra){
	Matrix colEntra = prob.ObtenerColumna(variableEntra);

	int indVariableSale = 0;
	for(unsigned i=0; i< variablesUsadas.size();i++){
		if(variablesUsadas[i] == variableSale)
		{
			indVariableSale = i;
			break;
		}
	}

	for(int i=0; i<base.getFilas() && i<colEntra.getFilas(); i++){
		base(i, indVariableSale) = colEntra(i, 0);
	}

	variablesUsadas[indVariableSale] = variableEntra;
}

int
SimplexSolver::getVariableSalida(int variableEntra){
	Matrix yk = baseInv*prob.ObtenerColumna(variableEntra);
	bool mayorcero = false;

	Rational min;
	int variableSale = -1;
	Matrix d = baseInv * prob.ObtenerD();

	for(int i =0; i< yk.getFilas(); i++){
		if(yk(i,0)>Rational::Cero){
			Rational aux = d(i, 0) / yk(i,0);
			if(!mayorcero)
			{
				min = aux;
				variableSale = variablesUsadas[i];
			}else{
				if(aux < min)
				{
					min = aux;
					variableSale = variablesUsadas[i];
				}
			}

			mayorcero = true;
		}
	}

	return variableSale;
}

int
SimplexSolver::getVariableSalidaDual(){
	int index = -1;
	Matrix dBarra = baseInv * prob.ObtenerD();

	Rational min;
	for(int i = 0; i < dBarra.getFilas(); i++){
		if(dBarra(i, 0) < Rational::Cero){
			if(index == -1){
				min = dBarra(i, 0);
				index = variablesUsadas[i];
			}

			if(dBarra(i, 0) < min){
				min = dBarra(i, 0);
				index = variablesUsadas[i];
			}
		}
	}

	return index;
}

int
SimplexSolver::getVariableEntradaDual(int varSale){
	int index = -1;

	vector<int> noBasicas = prob.ObtenerNoBasicas(variablesUsadas);

	//vector<int> ykj(noBasicas.size());

	vector<Rational> zjcj = getZJCJ();

	int varSaleIndex = -1;
	for(unsigned i = 0; varSaleIndex == -1 && i < variablesUsadas.size(); i++){
		if(variablesUsadas[i] == varSale){
			varSaleIndex = i;
		}
	}

	Rational minimo;

	for(unsigned i = 0; i < noBasicas.size(); i++){
		Matrix ykj = baseInv*prob.ObtenerColumna(noBasicas[i]);

		if(ykj(varSaleIndex, 0) < Rational::Cero){
			if(index == -1){
				minimo = zjcj[i] / ykj(varSaleIndex, 0);
				index = noBasicas[i];
			}

			if(zjcj[i] / ykj(varSaleIndex, 0) < minimo){
				minimo = zjcj[i] / ykj(varSaleIndex, 0);
				index = noBasicas[i];
			}
		}
	}

	return index;
}

int
SimplexSolver::getVariableEntra(){

	int columnas = base.getColumnas();

	Matrix cb(1,columnas);
	for(int i=0; i<columnas;i++)
	{
		cb(0,i) = prob.ObtenerCoeficienteFuncion(variablesUsadas[i]);
	}

	Matrix cbbInv = cb*baseInv;

	vector<int> noBasicas = prob.ObtenerNoBasicas(variablesUsadas);

	vector<Rational> zjcj = getZJCJ();

	Rational mayor(0);
	int variableEntra = -1;

	for(unsigned i = 0; i < zjcj.size(); i++){
		if(zjcj[i] > Rational::Cero){
			if(zjcj[i] > mayor){
				mayor = zjcj[i];
				variableEntra = noBasicas[i];
			}
		}
	}

	return variableEntra;
}

vector<Rational>
SimplexSolver::getZJCJ(){
	int columnas = base.getColumnas();

	Matrix cb(1,columnas);
	for(int i=0; i<columnas;i++)
	{
		cb(0,i) = prob.ObtenerCoeficienteFuncion(variablesUsadas[i]);
	}

	Matrix cbbInv = cb*baseInv;

	vector<int> noBasicas = prob.ObtenerNoBasicas(variablesUsadas);

	vector<Rational> zjcj(noBasicas.size());

	for(unsigned i=0; i<noBasicas.size(); i++){
		Matrix aux = cbbInv * prob.ObtenerColumna(noBasicas[i]);
		zjcj[i] = aux(0, 0) - prob.ObtenerCoeficienteFuncion(noBasicas[i]);
	}

	return zjcj;
}

void
SimplexSolver::checkRestriccionArtificial(){
	int varEntra = getVariableEntra();

	if(varEntra != -1){
		//Tenemos que aplicar la tecnica de la restriccion artificial...
		vector<int> noBasicas = prob.ObtenerNoBasicas(variablesUsadas);

		//Construimos la restriccion artificial
		Funcion f;
		for(unsigned i = 0; i < noBasicas.size(); i++){
			f.addTermino(Termino(1, noBasicas[i]));
		}

		f.setTipo(Funcion::MenorIgual);
		f.setResultado(Rational(CandyMath::INFINITO, 1));

		prob.addRestriccion(f);

		//Volvemos a normalizar y a sacar la base
		prob.NormalizarDual();
		base = prob.ObtenerBase();
		baseInv = base.Inversa();
		variablesUsadas = prob.ObtenerBasicas();

		int indSale = variablesUsadas.back();

		//Cambiamos entre A6 y el max(zjcj)
		vector<Rational> zjcj = getZJCJ();
		Rational mayor;
		int indEntra = -1;
		noBasicas = prob.ObtenerNoBasicas(variablesUsadas);
		for(unsigned i = 0; i < zjcj.size(); i++){
			if(indEntra == -1){
				mayor = zjcj[i];
				indEntra = noBasicas[i];
			}

			if(zjcj[i] > mayor){
				mayor = zjcj[i];
				indEntra = noBasicas[i];
			}
		}

		cambiarBase(indSale, indEntra);

		//varEntra = getVariableEntra();
	}
}

Rational
SimplexSolver::getOptimo(){
	xb = baseInv*prob.ObtenerD();

	vector<Rational> valores;
	for(int i = 0; i < xb.getFilas(); i++){
		valores.push_back(xb(i, 0));
	}
	optimo = prob.getFuncObjetivo().getResultado(variablesUsadas, valores);

	if(prob.getTipoProblema() == Problema::_MIN){
		optimo = -optimo;
	}

	return optimo;
}

vector<Rational>
SimplexSolver::getSolTemporales(vector<int> varObjetivo){
	vector<Rational> solTemporales(varObjetivo.size());
	for(unsigned i = 0; i < solTemporales.size(); i++){
		int indInXB = -1;
		for(unsigned j = 0; j < variablesUsadas.size() && indInXB == -1; j++){
			if(variablesUsadas[j] == i + 1){
				indInXB = j;
				solTemporales[i] = xb(indInXB, 0);
			}
		}
	}

	return solTemporales;
}

bool
SimplexSolver::EsSolucion(const SimplexNode& sn){
	bool solucionEntera = true;

	for(unsigned i = 0; i < sn._variables.size() && solucionEntera; i++){
		if(!sn._variables[i].isEntero()){
			solucionEntera = false;
		}
	}

	return solucionEntera;
}

vector<SimplexNode>
SimplexSolver::Expandir(const SimplexNode& sn){
	vector<SimplexNode> expandidos;
	//Buscamos la primera variable no entera
	Rational solActual(0);
	int indActual = -1;
	for(unsigned i = 0; i < sn._variables.size() && indActual == -1; i++){
		if(!sn._variables[i].isEntero()){
			indActual = i;
			solActual = sn._variables[i];
		}
	}

	//Si hay alguna variable no entera... (en teoria siempre deberia haber alguna)
	if(indActual != -1){
		//Añadimos los dos (redondeando por encima y por debajo)
		for(unsigned i = 0; i < 2; i++){
			//solTemporales = sn._variables;
			SimplexNode aux;
			aux._profundidad = sn._profundidad + 1;
			aux._prob = sn._prob;
			aux._optimo = sn._optimo;

			//Miramos que variable tenemos que añadir
			Funcion f;
			f.addTermino(Termino(1, indActual + 1));
			if(i == 0){
				f.setTipo(Funcion::MenorIgual);
				f.setResultado(solActual.RoundMin());
			}else{
				f.setTipo(Funcion::MayorIgual);
				f.setResultado(solActual.RoundMax());
			}
			aux._prob.addRestriccion(f);

			expandidos.push_back(aux);
		}
	}

	return expandidos;
}

bool
SimplexSolver::Aceptable(const SimplexNode& sn, const Rational& mejorOptimo, const vector<Rational>& mejorSolucion){
	bool aceptable = true;;

	if(mejorSolucion.size() > 0){
		//Si ya hay alguna cota...
		if(sn._prob.getTipoProblema() == Problema::MAX){
			//Si es maximizar...
			if(sn._optimo < mejorOptimo){
				aceptable = false;
			}else{
				aceptable = true;
			}
		}else if(sn._prob.getTipoProblema() == Problema::MIN){
			if(sn._optimo > mejorOptimo){
				aceptable = false;
			}else{
				aceptable = true;
			}
		}
	}else{
		aceptable = true;
	}

	return aceptable;
}

Rational
SimplexSolver::getOptimoFinal() const{
	return optimo;
}

vector<Rational>
SimplexSolver::getSoluciones() const{
	return soluciones;
}

SimplexSolver::ResultadoSimplex
SimplexSolver::getEstado() const{
	return estado;
};


} /* namespace candy */
