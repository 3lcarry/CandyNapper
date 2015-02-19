#include <iostream>
#include <cstdlib>
using namespace std;

#include "CandyMath.h"
using namespace candy;

const string USO = "USO: test-position X Y Z";

int main(int argc, char **argv) {
	if(argc == 4){
		Rational x = (float)atof(argv[1]);
		Rational y = (float)atof(argv[2]);
		Rational z = (float)atof(argv[3]);

		Vector3 pos(x, y, z);

		cout << pos << endl;
	}else{
		cout << USO << endl;
	}
}

