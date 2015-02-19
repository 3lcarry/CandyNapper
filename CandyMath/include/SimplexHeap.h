/*
 * SimplexHeap.h
 *
 *  Created on: 17/05/2012
 *      Author: kaseyo
 */

#ifndef SIMPLEXHEAP_H_
#define SIMPLEXHEAP_H_

#include "Rational.h"
#include "Problema.h"

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

namespace candy {

class SimplexNode{
	friend ostream& operator<<(ostream& os, const SimplexNode& sn);
public:
	SimplexNode();
	SimplexNode(const vector<Rational>& variables, const Rational& optimo, int profundidad, const Problema& prob);
	~SimplexNode();
	SimplexNode(const SimplexNode& node);
	SimplexNode& operator=(const SimplexNode& node);

	vector<Rational> _variables;
	Rational _optimo;
	int _profundidad;
	Problema _prob;

private:
	void copiarDesde(const SimplexNode& node);
};

class SimplexHeap {
public:
	SimplexHeap();
	~SimplexHeap();
	void Push(SimplexNode);
	SimplexNode Pop();
	bool Vacio();
	vector<SimplexNode> _heap;

private:
	static bool Ordenar(SimplexNode a, SimplexNode b);
};

} /* namespace candy */
#endif /* SIMPLEXHEAP_H_ */
