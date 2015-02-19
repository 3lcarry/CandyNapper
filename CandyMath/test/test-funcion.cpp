#include "CandyMath.h"
using namespace candy;

#include <vector>
#include <list>

using namespace std;

int main(int argc, char **argv) {
	/*
	list<Termino> terminos;
	terminos.push_back(Termino(3, 4));
	Funcion f(terminos);
	*/
	//Funcion f("X1 -4X0 +10X2 <= -2");

	vector<string> aux;
	/*
	aux.push_back("MAX 2X1 +1X2 +5X3 -3X4");
	aux.push_back("X1 +2X2 -1X3 +4X4 <= 6");
	aux.push_back("2X1 +3X2 +1X3 -1X4 <= 12");
	aux.push_back("X1 +1X3 +1X4 <= 4");
	*/
	/*
	aux.push_back("MIN 3X1 +1X2 +4X3 +8X4");
	aux.push_back("X1 +2X2 +5X3 +6X4 >= 8");
	aux.push_back("2X1 +5X2 +3X3 -5X4 <= 3");
	*/
	/*
	aux.push_back("MAX 2X1 -1X2");
	aux.push_back("1X1 +1X2 <= 3");
	aux.push_back("-1X1 +1X2 >= 1");
	*/
	/*
	aux.push_back("MAX -4X1 -6X2 -18X3");
	aux.push_back("1X1 +3X3 >= 3");
	aux.push_back("1X2 +2X3 >= 5");
	*/
	/*
	aux.push_back("MIN -1X1 +2X2");
	aux.push_back("-1X1 +1X2 <= 1");
	aux.push_back("-1X1 -1X2 <= -3");
	aux.push_back("1X1 -2X2 <= 2");
	*/

	aux.push_back("MAX 21X1 +11X2");
	aux.push_back("7X1 +4X2 <= 13");
	aux.push_back("1X1 >= 0");
	aux.push_back("1X2 >= 0");

	/*
	aux.push_back("MAX 21X1 +11X2");
	aux.push_back("7X1 +4X2 <= 13");
	aux.push_back("1X1 >= 0");
	aux.push_back("1X2 >= 0");
	aux.push_back("1X1 <= 1");
	aux.push_back("1X2 >= 2");
	aux.push_back("1X1 <= 0");
	*/
	Problema p(aux);

	cout << "PROBLEMAS: " << endl;
	cout << p << endl;


	SimplexSolver ss;

	cout << "RESOLVEMOS PROBLEMA CON SIMPLEX NORMAL" << endl;
	cout << "Optimo: " << ss.SimplexSolve(p) << endl;


	cout << "##########################################################################################" << endl;
	cout << "RESOLVEMOS PROBLEMA CON PENALIZACIONES" << endl;
	cout << "Optimo: " << ss.PenalizacionesSolve(p) << endl;


	cout << "##########################################################################################" << endl;
	cout << "RESOLVEMOS PROBLEMA CON DUAL" << endl;
	cout << "Optimo: " << ss.DualSimplexSolve(p) << endl;


	cout << "##########################################################################################" << endl;
	cout << "RESOLVEMOS PROBLEMA CON ENTEROS" << endl;
	cout << "Optimo: " << ss.IntSimplexSolve(p) << endl;

	/*
	vector<int> base = p.getIdentidadBase();
	cout << "Variables de la base: " << endl;
	for(int i = 0; i < base.size(); i++){
		cout << i + 1 << "[" << base[i] << "]" << " ";
	}

	cout << endl;

	cout << "A„ADIMOS VARIABLES ARTIFICIALES" << endl;
	p.addArtificiales();
	cout << p << endl;
	base = p.getIdentidadBase();
	cout << "Variables de la base: " << endl;
	for(int i = 0; i < base.size(); i++){
		cout << i + 1 << "[" << base[i] << "]" << " ";
	}
	cout << endl;
	*/

	//cout << "FUNCION: " << endl;
	//cout << f << endl;
/*
	cout << "VARIABLES: " << endl;
	list<int> lista = p.getVariables();
	list<int>::iterator it;
	for(it = lista.begin(); it != lista.end(); it++){
		cout << *it << " ";
	}
*/
/*
	cout << "NORMALIZAMOS" << endl;
	p.Normalizar();

	cout << p << endl;

	cout << "SACAMOS LA BASE" << endl;
	cout << p.ObtenerBase() << endl;

	cout << "SACAMOS D" << endl;
	cout << p.ObtenerD() << endl;

	cout << "RESOLVEMOS PROBLEMA" << endl;
	SimplexSolver ss;
	ss.Solve(p);
*/


	cout << endl;

}

