/*
 * Matrix.cpp
 *
 *  Created on: 09/01/2012
 *      Author: kaseyo
 */

#include "Matrix.h"

namespace candy {
Rational Matrix::_error = Rational::Cero;
const string Matrix::ERR_DIM = "ERROR: Las dimensiones no son correctas";

Matrix::Matrix(int dim) {

	if(dim > 0){
		_columnas = dim;
		_filas = dim;

		//Reservamos memoria para la matriz
		init();
	}else{
		cout << ERR_DIM << endl;
		_columnas = 0;
		_filas = 0;
		_matrix = NULL;
	}
}

Matrix::Matrix(int filas, int columnas){
	if(filas > 0 && columnas > 0){
		_columnas = columnas;
		_filas = filas;

		//Reservamos memoria para la matriz
		init();
	}else{
		cout << ERR_DIM << endl;
		_columnas = 0;
		_filas = 0;
		_matrix = NULL;
	}
}

void
Matrix::init(){
	_matrix = new Rational*[_filas];

	for(int i = 0; i < _filas; i++){
		_matrix[i] = new Rational[_columnas];

		for(int j = 0; j < _columnas; j++){
			if(i == j){
				_matrix[i][j] = Rational::Uno;
			}else{
				_matrix[i][j] = Rational::Cero;
			}
		}
	}
}

Matrix::~Matrix() {
	/*
	 * Deberia ser distinto de NULL, ya que se obliga en el constructor
	 * pero lo comprobamos por si acaso
	 */
	if(_matrix != NULL){
		for(int i = 0; i < _filas; i++){
			if(_matrix[i] != NULL){
				delete[] _matrix[i];
				_matrix[i] = NULL;
			}
		}
		delete[] _matrix;
		_matrix = NULL;
	}
}

Matrix::Matrix(const Matrix & cop){
	copiarDesde(cop);
}

Matrix&
Matrix::operator =(const Matrix & cop){
	if(this != &cop){
		this->~Matrix();
		copiarDesde(cop);
	}

	return *this;
}

ostream&
operator<<(ostream& os, const Matrix& matrix){
	for(int i=0; i < matrix._filas; i++){
		for(int j=0; j < matrix._columnas; j++){
			os << matrix._matrix[i][j];
			if(j < matrix._columnas - 1){
				os << "\t";
			}
		}

		if(i < matrix._filas - 1){
			os << endl;
		}
	}

	return os;
}

Rational
Matrix::operator()(int i, int j) const{
	Rational res = Rational::Cero;

	if(i < _filas){
		if(j < _columnas){
			res = _matrix[i][j];
		}
	}

	return res;
}

Rational&
Matrix::operator ()(int i, int j){
	_error = Rational::Cero;

	if(i < _filas){
		if(j < _columnas){
			return _matrix[i][j];
		}
	}

	return _error;
}

void
Matrix::copiarDesde(const Matrix & cop){
	_filas = cop._filas;
	_columnas = cop._columnas;

	//Reservamos memoria para la matriz
	_matrix = new Rational*[_filas];
	for(int i=0; i < _filas; i++){
		_matrix[i] = new Rational[_columnas];
		for(int j=0; j < _columnas; j++){
			_matrix[i][j] = cop._matrix[i][j];
		}
	}
}

Matrix
Matrix::operator +(const Matrix& m2) const{
	Matrix res(_filas, _columnas);

	if(_filas == m2._filas && _columnas == m2._columnas){
		for(int i = 0; i < _filas; i++){
			for(int j=0; j < _columnas; j++){
				res(i, j) = _matrix[i][j] + m2(i, j);
			}
		}
	}else{
		cout << ERR_DIM << endl;
	}

	return res;
}

Matrix
Matrix::operator -(const Matrix& m2) const{
	Matrix res(_filas, _columnas);

	if(_filas == m2._filas && _columnas == m2._columnas){
		for(int i = 0; i < _filas; i++){
			for(int j=0; j < _columnas; j++){
				res(i, j) = _matrix[i][j] - m2(i, j);
			}
		}
	}else{
		cout << ERR_DIM << endl;
	}

	return res;
}


Matrix
Matrix::operator *(const Rational & r1) const{

	Matrix res(_filas, _columnas);

	for(int i = 0; i < _filas; i++){
		for(int j=0; j < _columnas; j++){
			res(i, j) = _matrix[i][j] * r1;
		}
	}

	return res;

}

Matrix
Matrix::operator *(const Matrix& m1) const{
	Matrix res(_filas, m1._columnas);

	if(_columnas == m1._filas){
		for(int i = 0; i < _filas; i++){
			for(int j = 0; j < m1._columnas; j++){
				res._matrix[i][j] = Rational::Cero;
				for(int k=0; k < _columnas; k++){
					res._matrix[i][j] += _matrix[i][k] * m1._matrix[k][j];
				}
			}
		}
	}else{
		cout << ERR_DIM << endl;
	}

	return res;
}

Matrix
Matrix::Transpuesta(){
	Matrix res(_filas, _columnas);

	if(_matrix != NULL){
		for(int i = 0; i < _filas; i++){
			for(int j = 0; j < _columnas; j++){
				res._matrix[j][i] = _matrix[i][j];
			}
		}
	}

	return res;
}

Matrix
Matrix::Inversa(){
	Matrix res(*this);

	res.inversaAux();

	return res;
}

void
Matrix::inversaAux(){
	if(isCuadrada() && _matrix != NULL){
		int fil = 0;
		int col = 0;

		bool encontrado = false;

		Matrix inversa(_filas);

		//Busco la prim columna no-cero
		for(int i = 0; i < _columnas && !encontrado; i++){
			if(columNoCero(i)){
				col = i;
				encontrado = true;
			}
		}

		encontrado = true;
		//Diagonalizo
		Rational pivot;
		Rational aux;
		Rational multiplo;
		while(col < _columnas){
			//Si el elemento actual es 0, busco otro pivot debajo suya
			pivot = _matrix[fil][col];
/*
			cout << "[Matrix.cpp] Fila actual: " << fil << endl;
			cout << "[Matrix.cpp] Columna actual: " << col << endl;
			cout << "[Matrix.cpp] Como va la matriz: " << endl;
			cout << *this << endl;
			cout << "[Matrix.cpp] Como va la inversa:" << endl;
			cout << inversa << endl;
*/
			if(pivot == Rational::Cero){
				encontrado = false;
				//cout << "[Matrix.cpp] El pivot es cero, y sustituyo" << endl;
				for(int i = fil + 1; i < _filas && !encontrado; i++){
					aux = _matrix[i][col];
					if(aux != Rational::Cero){
						encontrado = true;
						swapFilas(fil, i);
						inversa.swapFilas(fil, i);
						pivot = aux;
					}
				}
/*
				cout << "[Matrix.cpp] Como va la matriz: " << endl;
				cout << *this << endl;
				cout << "[Matrix.cpp] Como va la inversa:" << endl;
				cout << inversa << endl;
*/
			}

			if(encontrado){
				//Hago mi pivot = '1' (sabiendo que no es 0)
				if(pivot != Rational::Uno){
					aux = pivot.Inversa();
					//cout << "[Matrix.cpp] Hago 1 el pivote " << pivot << " multiplicando por " << pivot.Inversa() << endl;
					multFila(fil, aux);
					inversa.multFila(fil, aux);

/*
					cout << "[Matrix.cpp] Como va la matriz: " << endl;
					cout << *this << endl;
					cout << "[Matrix.cpp] Como va la inversa:" << endl;
					cout << inversa << endl;
*/
				}

				//Hago 0s debajo suya (sabiendo que el pivot ahora es 1)
				for(int i = 0; i < _filas; i++){
					if(i != fil){
						aux = _matrix[i][col];
						if(aux != Rational::Cero){
							multiplo = -aux;
							//cout << "[Matrix.cpp] Hago 0 la fila " << i << " multiplicando por " << multiplo << endl;
							sumarFila(fil, i, multiplo);
							inversa.sumarFila(fil, i, multiplo);

/*
							cout << "[Matrix.cpp] Como va la matriz: " << endl;
							cout << *this << endl;
							cout << "[Matrix.cpp] Como va la inversa:" << endl;
							cout << inversa << endl;
*/
						}
					}
				}
			}

			col++;
			fil++;
		}

		//cout << "[Matrix.cpp] Resultado final: " << endl << *this << endl;

		*this = inversa;
	}
}

void
Matrix::multFila(int f1, const Rational& multiplo){
	if(_matrix != NULL){
		Rational* pRat = _matrix[f1];
		for(int i = 0; i < _columnas; i++){
			//cout << "[Matrix.cpp] Multiplico " << (*pRat) << " por " << multiplo << " = " << (*pRat) * multiplo << endl;
			(*pRat) *= multiplo;
			pRat++;
		}
	}
}

void
Matrix::divFila(int f1, const Rational& multiplo){
	if(_matrix != NULL){
		Rational* pRat = _matrix[f1];
		for(int i = 0; i < _columnas; i++){
			(*pRat) /= multiplo;
			pRat++;
		}
	}
}

void
Matrix::sumarFila(int f1, int f2, const Rational& multiplo){
	if(_matrix != NULL){
		Rational* pRat1 = _matrix[f1];
		Rational* pRat2 = _matrix[f2];
		for(int i = 0; i < _columnas; i++){
			(*pRat2) += multiplo * (*pRat1);
			pRat2++;
			pRat1++;
		}
	}
}

int
Matrix::getColumnas() const
{
	return _columnas;
}

int
Matrix::getFilas() const
{
	return _filas;
}

void
Matrix::swapFilas(int f1, int f2){
	if(_matrix != NULL){
		Rational* aux;

		if(f1 < _filas && f2 < _filas){
			aux = _matrix[f1];
			_matrix[f1] = _matrix[f2];
			_matrix[f2] = aux;
		}
	}
}

bool
Matrix::columNoCero(int col) const{
	bool cero = true;

	if(col < _columnas && _matrix != NULL){
		for(int i = 0; i < _filas && cero; i++){
			if(_matrix[i][col] != Rational::Cero){
				cero = false;
			}
		}
	}

	return cero;
}

bool
Matrix::filaNoCero(int fila) const{
	bool cero = true;

	if(fila < _filas && _matrix != NULL){
		Rational* pFila = _matrix[fila];
		for(int i = 0; i < _columnas && cero; i++){
			if(pFila[i] != Rational::Cero){
				cero = false;
			}
		}
	}

	return cero;
}

bool
Matrix::isCuadrada() const{
	return (_columnas == _filas);
}

bool
Matrix::isIdentidad() const{
	bool res = false;

	if(isCuadrada() && _matrix != NULL){
		res = true;
		for(int i = 0; i < _filas && res; i++){
			for(int j = 0; j < _columnas && res; j++){
				if(i == j){
					if(_matrix[i][j] != Rational::Uno){
						res = false;
					}
				}else{
					if(_matrix[i][j] != Rational::Cero){
						res = false;
					}
				}
			}
		}
	}

	return res;
}

} /* namespace candy */
