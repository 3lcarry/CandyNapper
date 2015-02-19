/*
 * CandyMath.h
 *
 *  Created on: 10/01/2012
 *      Author: kaseyo
 */

#ifndef CANDYMATH_H_
#define CANDYMATH_H_

#include <vector>
#include <list>
#include <cmath>
using namespace std;

namespace candy {
/**
 * @class CandyMath
 * Clase principal de la librería matemática CandyMath. Incluye las cabeceras al resto de modulos, además de métodos "generales".
 */
namespace CandyMath {
	/**
	 * Calcula el M.C.D entre dos enteros
	 * @param num1 Primer numero
	 * @param num2 Segundo numero
	 * @return Devuelve el MCD
	 */
	long long MCD(long long num1, long long num2);

	/**
	 * Calcula el M.C.M entre dos enteros
	 * @param num1 Primer numero
	 * @param num2 Segundo numero
	 * @return Minimo Comun Multiplo
	 */
	long long MCM(long long num1, long long num2);

	/**
	 * Calcula el maximo entre dos numeros
	 * @param num1 Numero 1
	 * @param num2 Numero 2
	 * @return Valor maximo entre num1 y num2
	 */
	long long Max(long long num1, long long num2);

	/**
	 * Calcula el minimo entre dos numeros
	 * @param num1 Numero 1
	 * @param num2 Numero 2
	 * @return Valor minimo entre num1 y num2
	 */
	long long Min(long long num1, long long num2);

	/**
	 * Calcula los divisores de un determinado numero.
	 * @param num Numero del que sacamos los divisores
	 * @param max Numero maximo hasta el que llegamos para sacar los divisores
	 * @return Vector con los divisores
	 */
	vector<long long> Divisores(long long num, long long max = -1);

	/**
	 * Calcula el valor absoluto de un numero
	 * @param num Numero del que sacamos su valor absoluto
	 * @return Devuelve el valor absoluto de num
	 */
	long long Abs(long long num);

	/**
	 * Calcula la potencia de 10 elevado a exp.
	 * @param exp Exponente al que elevamos 10
	 * @return Potencia de 10
	 */
	long long Pot10(long long exp);

	/**
	 * Transforma de grados a radianes
	 * @param grados Grados
	 * @return Radianes
	 */
	float grad2rad(float grados);

	/**
	 * Transforma de radianes a grados
	 * @param rad Radianes
	 * @return Grados
	 */
	float rad2grad(float rad);

	/**
	 * Halla el siguiente divisor
	 * @param numero Numero del que buscamos el divisor
	 * @param antDiv Divisor anterior
	 * @return Nuevo divisor
	 */
	long long findNextDivisor(long long numero, long long antDiv);

	/**
	 * Devuelve el signo de un numero (1 o -1)
	 * @param numero Numero entero
	 * @return 1 o -1
	 */
	long long Signo(long long numero);

	/**
	 * Hace un merge entre dos listas de enteros ordenadas
	 * @param l1 Primera lista
	 * @param l2 Segunda lista
	 * @return Union de las dos listas (sin duplicados)
	 */
	list<int> Merge(const list<int>& l1, const list<int>& l2);

	/**
	 * Constante que representa el valor infinito
	 */
	const int INFINITO = 99999;

} /* namespace CandyMath */

} /* namespace candy */
#endif /* CANDYMATH_H_ */
