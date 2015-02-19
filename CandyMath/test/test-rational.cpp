#include <iostream>
#include <cstdlib>
using namespace std;

#include "Rational.h"
using namespace candy;

const string USO = "test-rational num1 den1 num2 den2 | test-rational float1 float2";

int main(int argc, char **argv) {
	if(argc == 3){
		int num11 = atoi(argv[1]);
		int num12 = atoi(argv[2]);
		Rational r1(num11, num12);
		cout << "Fraccion (" << num11 << " , " << num12 << "): " << r1 << endl;

		cout << "Redondeo max: " << r1.RoundMax() << endl;
		cout << "Redondeo min: " << r1.RoundMin() << endl;


/*
		int num21 = atoi(argv[3]);
		int num22 = atoi(argv[4]);
*/
		/*
		Rational r2 = r1.Inversa();
		cout << "Fraccion (" << r2.getNumerador() << " , " << r2.getDenominador() << "): " << r2 << endl;

		cout << "SUMA" << endl;
		cout << r1+r2 << " - " << (float)(r1+r2) << endl;

		cout << "RESTA" << endl;
		cout << r1-r2 << " - " << (float)(r1-r2) << endl;

		cout << "PRODUCTO" << endl;
		cout << r1*r2 << " - " << (float)(r1*r2) << endl;

		cout << "DIVISION" << endl;
		cout << r1/r2 << " - " << (float)(r1/r2) << endl;
		*/
	}else if(argc == 80){
		float f1 = atof(argv[1]);
		Rational r1(f1);
		cout << "Fraccion (" << f1 << "): " << r1 << endl;


		float f2 = atof(argv[2]);
		Rational r2(f2);
		cout << "Fraccion (" << f2 << "): " << r2 << endl;

		cout << "SUMA" << endl;
		cout << r1+r2 << " - " << (float)(r1+r2) << endl;

		cout << "RESTA" << endl;
		cout << r1-r2 << " - " << (float)(r1-r2) << endl;

		cout << "PRODUCTO" << endl;
		cout << r1*r2 << " - " << (float)(r1*r2) << endl;

		cout << "DIVISION" << endl;
		cout << r1/r2 << " - " << (float)(r1/r2) << endl;
	}else{
		cout << USO << endl;
	}
}

