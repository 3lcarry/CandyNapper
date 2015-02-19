#include "CandyMath.h"
using namespace candy;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

void imprimirArray16(float* matriz){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			cout << matriz[j*4 + i] << "\t";
		}
		cout << endl;
	}
}

int num_random(){
	int res = rand();

	if(res % 20 == 0){
		res *= -1;
	}

	return res % 5;
}

int main(int argc, char **argv) {
	srand ( time(NULL) );

	Mat4 mat41;
	Mat4 mat42;


	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			mat41(i, j) = num_random();
		}
	}


	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			mat42(i, j) = num_random();
		}
	}

	imprimirArray16(mat41.getMatrix());
	cout << " * " << endl;
	imprimirArray16(mat42.getMatrix());
	cout << " = " << endl;
	imprimirArray16((mat41*mat42).getMatrix());
}
