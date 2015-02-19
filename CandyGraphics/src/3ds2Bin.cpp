#include <iostream>
#include <fstream>
#include "CandyGraphics.h"
using namespace std;

const string USO = "USO: 3ds2Bin input.3ds output.bin";
const string ERROR = "ERROR: La malla es demasiado grande";
const string ERROR_AP = "ERROR: No se pudo abrir ";
const string ERROR_ES = "ERROR: No se ha escrito bien";
const string OK = "OK: El binario se ha guardado bien";


int main(int argc, char* argv[]){
	if(argc == 3){
		string inputFile = argv[1];
		string outputFile = argv[2];

		//BinMesh m;
		float* malla;
		int size;
		malla = Load3DS(inputFile.c_str(), &size);
		int arraySize = size * 8;

		//if(MESHSIZE >= arraySize){
			//m.size = size;
			//m.mesh = new float[arraySize];

			ofstream fileOut;
			fileOut.open(outputFile.c_str(), ios::binary);
			if(fileOut.is_open()){
				fileOut.write((char*)&arraySize, sizeof(int));
				fileOut.write((char*)&size, sizeof(int));
				fileOut.write((char*)malla, sizeof(float) * arraySize);
				fileOut.close();
			}else{
				cout << ERROR_AP << outputFile << endl;
			}

			//Probamos a leerlo a ver si es todo igual...
			ifstream fileIn;
			fileIn.open(outputFile.c_str(), ios::binary);
			int arraySizeLeido;
			int sizeLeido;
			float* mallaLeido;
			if(fileIn.is_open()){
				fileIn.read((char*)&arraySizeLeido, sizeof(int));
				fileIn.read((char*)&sizeLeido, sizeof(int));
				mallaLeido = new float[arraySizeLeido];
				fileIn.read((char*)mallaLeido, sizeof(float) * arraySizeLeido);
				bool error = false;

				if(arraySizeLeido != arraySize){
					error = true;
				}

				if(sizeLeido != size){
					error = true;
				}

				for(int i = 0; i < arraySizeLeido && !error; i++){
					//if(i < m.size){
						if(mallaLeido[i] != malla[i]){
							error = true;
							cout << ERROR_ES << endl;
						}
					//}
				}

				if(!error){
					cout << OK << endl;
				}

				fileIn.close();
			}

		//}else{
			//cout << ERROR << " (MAX: " << MESHSIZE << ")" << endl;
		//}

	}else{
		cout << USO << endl;
	}
}
