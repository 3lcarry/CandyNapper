/*
 * Matrix.h
 *
 *  Created on: 09/01/2012
 *      Author: kaseyo
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
using namespace std;

#include "Rational.h"

namespace candy {

/**
 * @class Matrix
 * @brief Matriz de dimensiones generica.
 * Matriz cuadrada con tama�o generico. Guarda una matriz de punteros a float y permite operar con ella.
 */
class Matrix {
public:
	/**
	 * Sobrecarga del operador salida para la clase Matrix
	 * @param os Ostream de salida
	 * @param matrix Matriz que imprimimos
	 * @return Ostream modificados
	 */
	friend ostream& operator<<(ostream& os, const Matrix& matrix);

	/**
	 * Constructor a partir de un tama�o (es obligatorio especificarlo).
	 * Tambi�n inicializa los elementos a 0.
	 * @param dim Dimension de la matriz
	 */
	Matrix(int dim = 1);

	/**
	 * Constructor a partir del numero de filas y de columnas (para matrices no cuadradas)
	 * @param filas Numero de filas
	 * @param columnas Numero de columnas
	 */
	Matrix(int filas, int columnas);

	/**
	 * Destructor por defecto
	 */
	~Matrix();

	/**
	 * Constructor de copia
	 * @param cop Origen de la copia
	 */
	Matrix(const Matrix& cop);

	/**
	 * Operador igual
	 * @param cop Origen de la copia
	 * @return Resultado de la copia
	 */
	Matrix& operator=(const Matrix& cop);

	/**
	 * Devuelve el numero que ocupa la posicion i,j en la matriz. 0 por defecto.
	 * @param i Numero de fila
	 * @param j Numero de columna
	 * @return Numero en la posicion [i,j]
	 */
	 Rational operator()(int i, int j) const;

	 /**
	  * Inserta un numero en la posicion i, j. Si se pasa de rango devuelve el float "c_error".
	  * @param i Numero de fila
	  * @param j Numero de columna
	  */
	 Rational& operator()(int i, int j);

	 /**
	  * Operador suma de matrices
	  * @param m1 Matriz que sumamos
	  * @return Resultado de la suma
	  */
	 Matrix operator+(const Matrix& m1) const;

	 /**
	  * Operador resta de matrices
	  * @param m1 Matriz que restamos
	  * @return Resultado de la resta
	  */
	 Matrix operator-(const Matrix& m1) const;

	 /**
	  * Operador producto por un escalar (un racional)
	  * @param r1 Escalar que multiplicamos
	  * @return Resultado de la operacion
	  */
	 Matrix operator*(const Rational& r1) const;

	 /**
	  * Operador producto por otra matriz
	  * @param m1 Matriz que multiplicamos
	  * @return Resultado de la multiplicacion
	  */
	 Matrix operator*(const Matrix& m1) const;

	 /**
	  * Obtiene la transpuesta de la matriz
	  * @return Matriz transpuesta
	  */
	 Matrix Transpuesta();

	 /**
	  * Obtiene la inversa de la matriz
	  * @return Matriz inversa
	  */
	 Matrix Inversa();

	 /**
	  * Indica si una matriz es la identidad
	  * @return TRUE si es la identidad
	  */
	 bool isIdentidad() const;

	/**
	 * Indica si una matriz es o no cuadrada
	 * @return TRUE si es cuadrada
	 */
	bool isCuadrada() const;

	int getColumnas() const;

	int getFilas() const;

private:

	 /**
	  * Funcion auxiliar que permite copiar un objeto 'cop' en el nuestro
	  * @param cop Origen de la copia
	  */
	 void copiarDesde(const Matrix& cop);

	/**
	 * Matriz de punteros a float que guarda la matriz
	 */
	Rational** _matrix;

	/**
	 * Metodo que reserva memoria para el vector (llamado en varios constructores)
	 */
	void init();

	/**
	 * Metodo privado que realiza la inversa sobre la propia matriz (machaca la actual)
	 */
	void inversaAux();

	/**
	 * Realiza la operacion f2 <- multiplo*f1 + f2
	 * @param f1 Fila 1
	 * @param f2 Fila 2
	 * @param multiplo Multiplo que sumamos
	 */
	void sumarFila(int f1, int f2, const Rational& multiplo);

	/**
	 * Multiplica la fila por un multiplo
	 * @param f1 Fila que multiplicamos
	 * @param multiplo Multiplo
	 */
	void multFila(int f1, const Rational& multiplo);

	/**
	 * Divide la fila por un elemento
	 * @param f1 Fila que dividimos
	 * @param div Dividendo
	 */
	void divFila(int f1, const Rational& div);

	/**
	 * Indica si una columna es cero
	 * @param col Numero de columna
	 * @return TRUE si no es cero
	 */
	bool columNoCero(int col) const;

	/**
	 * Indica si una fila es cero
	 * @param fila Numero de fila
	 * @return TRUE si no es cero
	 */
	bool filaNoCero(int fila) const;

	/**
	 * Intercambia dos filas entre si
	 * @param f1 Fila 1
	 * @param f2 Fila 2
	 */
	void swapFilas(int f1, int f2);

	/**
	 * Numero de columnas
	 */
	int _columnas;

	/**
	 * Numero de filas
	 */
	int _filas;

	/**
	 * Elemento de "error" para cuando necesitamos devolver una referencia no valida
	 */
	static Rational _error;

	/**
	 * Error de dimensiones incorrectas.
	 */
	static const string ERR_DIM;
};

} /* namespace candy */
#endif /* MATRIX_H_ */
