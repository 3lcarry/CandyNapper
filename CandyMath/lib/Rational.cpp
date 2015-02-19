/*
 * Rational.cpp
 *
 *  Created on: 10/01/2012
 *      Author: kaseyo
 */

#include "Rational.h"

namespace candy {

const Rational Rational::Cero((long long)(0));
    const Rational Rational::Uno((long long )(1));
    const string Rational::ERROR_1 = "-----------------\nERROR: No se puede dividir por 0 (";
    const string Rational::ERROR_2 = ")\n-----------------";
    const int Rational::NUM_DEC = 2;
    ostream & operator <<(ostream & os, const Rational & rat)
    {
        os << rat.c_num;
        if(rat.c_den != 1 && rat.c_den != -1){
            os << "/" << rat.c_den;
        }
        return os;
    }

    Rational::Rational()
    {
        c_num = 0;
        c_den = 1;
    }

    Rational::Rational(long long  numerador, long long  denominador)
    {
        if(denominador == 0){
            cout << ERROR_1 << c_num << "/" << c_den << ERROR_2 << endl;
            c_num = 1;
            c_den = 1;
        }else
            if(denominador < 0){
                //Nos aseguramos de que el signo negativo este arriba o de que se eliminen los signos negativos
                c_num = -numerador;
                c_den = -denominador;
            }else{
                c_num = numerador;
                c_den = denominador;
            }

        simplificar();
    }

    Rational::Rational(long long  numerador)
    {
        c_num = numerador;
        c_den = 1;
    }

    Rational::Rational(int numerador)
    {
        c_num = (long long )(numerador);
        c_den = 1;
    }

    Rational::Rational(float decimal)
    {
        long long pot10 = CandyMath::Pot10(NUM_DEC);
        c_num = decimal * pot10;
        c_den = pot10;
        simplificar();
        //cout << "[Rational.cpp] Estoy casteando desde float" << endl;
    }

    Rational::Rational(double decimal)
    {
        long long pot10 = CandyMath::Pot10(NUM_DEC);
        c_num = decimal * pot10;
        c_den = pot10;
        simplificar();
    }

    Rational::~Rational()
    {
        c_num = 0;
        c_den = 0;
    }

    Rational::Rational(const Rational & cop)
    {
        copiarDesde(cop);
    }

    Rational & Rational::operator =(const Rational & cop)
    {
        if(this != &cop){
            copiarDesde(cop);
        }
        return *this;
    }

    Rational::operator float() const
    {
        float res = 0;
        if(c_den == 0){
            cout << ERROR_1 << *this << ERROR_2 << endl;
            ;
        }else{
            res = ((float)((c_num))) / ((float)((c_den)));
        }
        //cout << "[Rational.cpp] Estoy casteando a float" << endl;
        return res;
    }

    Rational Rational::operator +(const Rational & otro) const
    {
        long long den_comun = CandyMath::MCM(c_den, otro.c_den);
        long long mult1 = den_comun / c_den;
        long long mult2 = den_comun / otro.c_den;
        Rational res(c_num * mult1 + otro.c_num * mult2, den_comun);
        return res;
    }

    void Rational::operator +=(const Rational & otro)
    {
        long long den_comun = CandyMath::MCM(c_den, otro.c_den);
        long long mult1 = den_comun / c_den;
        long long mult2 = den_comun / otro.c_den;
        c_num = c_num * mult1 + otro.c_num * mult2;
        c_den = den_comun;
        simplificar();
    }

    Rational Rational::operator -(const Rational & otro) const
    {
        long long den_comun = CandyMath::MCM(c_den, otro.c_den);
        long long mult1 = den_comun / c_den;
        long long mult2 = den_comun / otro.c_den;
        Rational res(c_num * mult1 - otro.c_num * mult2, den_comun);
        return res;
    }

    void Rational::operator -=(const Rational & otro)
    {
        long long den_comun = CandyMath::MCM(c_den, otro.c_den);
        long long mult1 = den_comun / c_den;
        long long mult2 = den_comun / otro.c_den;
        c_num = c_num * mult1 - otro.c_num * mult2;
        c_den = den_comun;
        simplificar();
    }

    Rational Rational::operator -() const
    {
        Rational res(-c_num, c_den);
        return res;
    }

    Rational Rational::operator *(const Rational & otro) const
    {
        /*
	long long num;
	long long den;

	long long num1 = CandyMath::Abs(c_num);
	long long den1 = CandyMath::Abs(c_den);

	long long num2 = CandyMath::Abs(otro.c_num);
	long long den2 = CandyMath::Abs(otro.c_den);

	if(num1 == den2){
		if(den1 == num2){
			num = CandyMath::Signo(c_num) * CandyMath::Signo(otro.c_den);
			den = CandyMath::Signo(c_den) * CandyMath::Signo(otro.c_num);
		}else{
			num = otro.c_num * CandyMath::Signo(c_num);
			den = c_den * CandyMath::Signo(otro.c_den);
		}
	}else{
		if(den1 == num2){
			num = c_num * CandyMath::Signo(otro.c_num);
			den = otro.c_den * CandyMath::Signo(c_den);
		}else{
			num = c_num * otro.c_num;
			den = c_den * otro.c_den;
		}
	}
	*/
        Rational res(c_num * otro.c_num, c_den * otro.c_den);
        return res;
    }

    void Rational::operator *=(const Rational & otro)
    {
        long long num1 = CandyMath::Abs(c_num);
        long long den1 = CandyMath::Abs(c_den);
        long long num2 = CandyMath::Abs(otro.c_num);
        long long den2 = CandyMath::Abs(otro.c_den);
        /*
	if(num1 == den2){
		if(den1 == num2){
			c_num = CandyMath::Signo(c_num) * CandyMath::Signo(otro.c_den);
			c_den = CandyMath::Signo(c_den) * CandyMath::Signo(otro.c_num);
		}else{
			c_num = otro.c_num * CandyMath::Signo(c_num);
			c_den = c_den * CandyMath::Signo(otro.c_den);
		}
	}else{
		if(den1 == otro.c_num){
			c_num = c_num * CandyMath::Signo(otro.c_num);
			c_den = otro.c_den * CandyMath::Signo(c_den);
		}else{
			c_num = c_num * otro.c_num;
			c_den = c_den * otro.c_den;
		}
	}
*/
        c_num *= otro.c_num;
        c_den *= otro.c_den;
        simplificar();
    }

    Rational Rational::operator /(const Rational & otro) const
    {
        Rational res(c_num * otro.c_den, c_den * otro.c_num);
        return res;
    }

    void Rational::operator /=(const Rational & otro)
    {
        c_num *= otro.c_den;
        c_den *= otro.c_num;
        simplificar();
    }

    Rational Rational::operator /(long long  otro) const
    {
        Rational res(c_num, c_den * otro);
        return res;
    }

    void Rational::operator /=(long long  otro)
    {
        c_den *= otro;
        simplificar();
    }

    Rational Rational::Inversa() const
    {
        Rational res(c_den, c_num);
        return res;
    }

    bool Rational::operator !=(const Rational & otro) const
    {
        return ((c_num != otro.c_num) || (c_den != otro.c_den));
    }

    bool Rational::operator ==(const Rational & otro) const
    {
        return ((c_num == otro.c_num) && (c_den == otro.c_den));
    }

    void Rational::copiarDesde(const Rational & cop)
    {
        c_num = cop.c_num;
        c_den = cop.c_den;
}

bool
Rational::operator <=(const Rational & otro) const {
	bool menor = false;

	Rational aux = this->operator -(otro);
	if(aux.c_num <= 0){
		menor = true;
	}

	return menor;
}

bool
Rational::operator <(const Rational & otro) const {
	bool menor = false;

	Rational aux = this->operator -(otro);
	if(aux.c_num < 0){
		menor = true;
	}

	return menor;
}

bool
Rational::operator >=(const Rational & otro) const {
	bool mayor = false;

	Rational aux = this->operator -(otro);
	if(aux.c_num >= 0){
		mayor = true;
	}

	return mayor;
}

bool
Rational::operator >(const Rational & otro) const {
	bool mayor = false;

	Rational aux = this->operator -(otro);
	if(aux.c_num > 0){
		mayor = true;
	}

	return mayor;
}

void
Rational::simplificar(){
	if(c_num != 0){
		long long m_c_d = CandyMath::MCD(c_num, c_den);

/*
		cout << "[Rational.cpp] Simplifico: " << endl;
		cout << "[Rational.cpp] El mcd de " << c_num << " y " << c_den << " es " << m_c_d << endl;
		cout << "[Rational.cpp] El num pasa de " << c_num << " a " << c_num / m_c_d << endl;
		cout << "[Rational.cpp] El den pasa de " << c_den << " a " << c_den / m_c_d << endl;
*/

		c_num /= m_c_d;
		c_den /= m_c_d;
	}else{
		c_num = 0;
		c_den = 1;
	}
}

long long
Rational::getDenominador() const{
	return c_den;
}

long long
Rational::getNumerador() const {
	return c_num;
}

Rational
Rational::RoundMax() const{
	Rational max = *this;

	if(max.getDenominador() != 1){
		float fraccion = max;
		float parteEntera;
		modf(fraccion, &parteEntera);

		max = Rational(parteEntera + 1, 1);
	}

	return max;
}

Rational
Rational::RoundMin() const{
	Rational min = *this;

	if(min.getDenominador() != 1){
		float fraccion = min;
		float parteEntera;
		modf(fraccion, &parteEntera);

		min = Rational(parteEntera, 1);
	}

	return min;
}

bool
Rational::isEntero() const{
	return (c_den == 1);
}

} /* namespace candy */
