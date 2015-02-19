#include "Matrix.h"
using namespace candy;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

const string USO = "test-matrix (FIL1 COL1 FIL2 COL2) | DIM";

int num_random(){
	int res = rand();

	if(res % 20 == 0){
		res *= -1;
	}

	return res % 10;
}

Matrix matriz_random(int filas, int columnas){
	Matrix m1(filas, columnas);

	for(int i=0; i < filas; i++){
		for(int j=0; j < columnas; j++){
			m1(i, j) = num_random();
		}
	}

	return m1;
}


int main(int argc, char **argv) {
	if(argc == 5 || argc == 2){
		/* initialize random seed: */
		srand ( time(NULL) );
		//Llamamos a rand() % loqsea;

		int fil1;
		int col1;
		int fil2;
		int col2;

		if(argc == 5){
			fil1 = atoi(argv[1]);
			col1 = atoi(argv[2]);
			fil2 = atoi(argv[3]);
			col2 = atoi(argv[4]);
		}else if(argc == 2){
			fil1 = atoi(argv[1]);
			col1 = fil1;
			fil2 = fil1;
			col2 = fil1;
		}

		cout << "Rellenamos matriz 1..." << endl;

		Matrix m1 = matriz_random(fil1, col1);

		cout << m1 << endl << endl;
/*
		cout << "Rellenamos matriz 2..." << endl;

		Matrix m2 = matriz_random(fil2, col2);

		cout << m2 << endl << endl;
*/
/*
		cout << "SUMA: " << endl;
		cout << m1 + m2 << endl << endl;

		cout << "RESTA: " << endl;
		cout << m1 - m2 << endl << endl;

		cout << "PROD ESCALAR (*3/4): " << endl;
		Rational r1(3, 4);
		cout << m1 * r1 << endl;

		cout << "PRODUCTO: " << endl;
		cout << m1 * m2 << endl;
/*
		cout << "TRANSPUESTA: " << endl;
		cout << m1.Transpuesta() << endl;

		cout << "DETERMINANTE: " << endl;
		cout << m1.Determinante() << endl;
*/

		bool error = false;
		for(int i = 0; i < 1 && !error; i++){
			m1 = matriz_random(fil1, col1);
			cout << "CALCULO LA INVERSA..." << endl;
			Matrix aux = m1.Inversa();
/*
			cout << "INVERSA: " << endl;
			cout << aux << endl;
*/

			cout << "ORIGINAL: " << endl;
			cout << m1 << endl;

			cout << "MULTIPLICO POR LA INVERSA: " << endl;
			aux = m1 * aux;
			cout << aux << endl;

			if(!aux.isIdentidad()){
				cout << "NO VA BIEN!" << endl;
				error = true;
			}

		}


	}else{
		cout << USO << endl;
	}

	return 1;
}
