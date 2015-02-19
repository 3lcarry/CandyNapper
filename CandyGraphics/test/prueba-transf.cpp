#include "Transformation.h"

using namespace candy;

int main(int argc, char **argv) {
	Transformation t1;
	Vector3 p(3.2, 4.1, 5.5);

/*
	t1.Translate(p);
	cout << "TRANSLACION " << p << endl;
	cout << t1.getMatrix() << endl;
*/

	//Supongamos que queremos rotar 100 entidades..., con la misma matriz
	for(int i = 0; i < 100; i++){
		//t1.Rotate(1, 45.3);
		t1.Translate(p);

		cout << "------" << i << "----" << endl;
		cout << t1.getMatrix() << endl;
	}

/*
	Transformation t2;

	Rational grados = 45.3;
	t1.Rotate(1, grados);
	cout << "Rotacion (" << grados << ")"  << endl;
	cout << t1.getMatrix() << endl;

	Transformation t3;

	t1.Scale(p);
	cout << "Escalado " << p  << endl;
	cout << t1.getMatrix() << endl;
*/
}
