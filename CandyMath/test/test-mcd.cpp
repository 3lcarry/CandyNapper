#include "CandyMath.h"
using namespace candy;

#include <iostream>
#include <cstdlib>
using namespace std;

const string USO = "test-mcd num1 num2";

int num_random(){
	int res = rand();

	return res % 54729;
}

int mcd(int num1, int num2){
	int res = 1;
	int min = CandyMath::Min(num1, num2);


	//Calculamos los divisores hasta el min
	vector<long long> div_1 = CandyMath::Divisores(CandyMath::Abs(num1), min);
	vector<long long> div_2 = CandyMath::Divisores(CandyMath::Abs(num2), min);


	vector<long long>::iterator itI = div_1.begin();
	vector<long long>::iterator itJ = div_2.begin();

	while(itI != div_1.end() && itJ != div_2.end()){
		if(*itI < *itJ){
			itI++;
		}else if(*itI > *itJ){
			itJ++;
		}else{
			//div_1[i] y div_2[j] son iguales
			res = *itI;
			itI++;
			itJ++;
		}
	}

	return res;
}


int main(int argc, char **argv) {
	/* initialize random seed: */
	srand ( time(NULL) );

	long long num1 = 2589468633, num2 = 2589468633;

	if(argc == 3){
		//num1 = atoi(argv[1]);
		//num2 = atoi(argv[2]);
	}else{
		num1 = num_random();
		num2 = num_random();
	}

	bool error = false;
	for(int i = 0; i < 1 && !error; i++){
		//num1 = num_random() + 1;
		//num2 = num_random() + 1;

		long long viejo = mcd(num1, num2);
		long long nuevo = CandyMath::MCD(num1, num2);

		cout << "MCD nueva ver(" << num1 << " , " << num2 << "): " << nuevo << endl;
		cout << "MCD viejo(" << num1 << " , " << num2 << "): " << viejo << endl;

		if(viejo != nuevo){
			cout << "SON DISTINTOS!!!!" << endl;
			error = true;
		}
	}

	//cout << "MCM (" << num1 << " , " << num2 << "): " << CandyMath::MCM(num1, num2) << endl;

}
