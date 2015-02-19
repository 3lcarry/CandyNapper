/*
 * CandyMath.cpp
 *
 *  Created on: 10/01/2012
 *      Author: kaseyo
 */

#include "Common.h"

#include <iostream>
#include <cmath>
using namespace std;

namespace candy {

long long
CandyMath::MCD(long long num1, long long num2){
	//Algoritmo de euclides
	long long a = Abs(num1);
	long long b = Abs(num2);

	long long aux;

	while(b != 0){
		aux = b;
		b = a % b;
		a = aux;
	}

	return a;
}

list<int>
CandyMath::Merge(const list<int>& l1, const list<int>& l2){
	list<int> res;

	list<int>::iterator itRes = res.begin();
	list<int>::const_iterator it1 = l1.begin();
	list<int>::const_iterator it2 = l2.begin();

	while(it1 != l1.end() && it2 != l2.end()){
		if(*it1 == *it2){
			res.push_back(*it1);
			it1++;
			it2++;
		}else if(*it1 < *it2){
			res.push_back(*it1);
			it1++;
		}else if(*it1 > *it2){
			res.push_back(*it2);
			it2++;
		}
	}

	if(it1 != l1.end()){
		res.insert(res.end(), it1, l1.end());
	}else if(it2 != l2.end()){
		res.insert(res.end(), it2, l2.end());
	}


	return res;
}

long long
CandyMath::MCM(long long num_1, long long num_2){
	/*
	int num1 = Abs(num_1);
	int num2 = Abs(num_2);

	int mult1 = num1;
	int mult2 = num2;

	int res = 0;

	while(res == 0){
		if(mult1 == mult2){
			res = mult1;
		}else if(mult1 < mult2){
			mult1 += num1;
		}else{
			mult2 += num2;
		}
	}
	*/

	long long res = (Abs(num_1) / MCD(num_1, num_2)) * Abs(num_2);

	return res;
}

long long
CandyMath::Max(long long num1, long long num2){
	long long res = num2;

	if(num1 > num2){
		res = num1;
	}

	return res;
}

long long
CandyMath::Min(long long num1, long long num2){
	long long res = num2;

	if(num1 < num2){
		res = num1;
	}

	return res;
}

vector<long long>
CandyMath::Divisores(long long num, long long max){
	vector<long long> divisores;
	if(max == -1 || max > num){
		max = num;
	}

	for(long long i=1; i <= max; i++){
		if(num % i == 0){
			//Anyadimos el numero
			divisores.push_back(i);
		}
	}

	return divisores;
}

long long
CandyMath::findNextDivisor(long long num, long long antDiv){
	long long res = 1;
	bool encontrado = false;

	for(long long i = antDiv + 1; i <= num && !encontrado; i++){
		if(num % i == 0){
			res = i;
			encontrado = true;
		}
	}

	return res;
}

long long
CandyMath::Abs(long long num){
	if(num < 0){
		num *= -1;
	}

	return num;
}

long long
CandyMath::Pot10(long long exp){
	long long res = 1;

	for(long long i=0; i < exp; i++){
		res *= 10;
	}

	return res;
}

float
CandyMath::grad2rad(float grados){
	float radianes;

	radianes = grados * M_PI / 180.0;

	return radianes;
}

float
CandyMath::rad2grad(float radianes){
	float grados;

	grados = radianes * 180.0 / M_PI;

	return grados;
}

long long
CandyMath::Signo(long long numero){
	long long res = 1;

	if(numero < 0){
		res = -1;
	}

	return res;
}

} /* namespace candy */
