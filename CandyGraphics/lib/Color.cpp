#include "Color.h"

namespace candy {

Color Color::Blue(0, 0, 1, 1);
Color Color::Red(1, 0, 0, 1);
Color Color::Green(0, 1, 0, 1);
Color Color::Yellow(1, 1, 0, 1);
Color Color::Cyan(0, 1, 1, 1);
Color Color::Magenta(1, 0, 1, 1);
Color Color::Brown(0.6, 0.3, 0, 1);
Color Color::Orange(1, 0.5, 0, 1);
Color Color::Purple(0.5, 0, 0.5, 1);
Color Color::Black(0, 0, 0, 1);
Color Color::White(1, 1, 1, 1);

Color::Color(){
	r = 1;
	g = 1;
	b = 1;
	a = 1;
}

Color::Color(float red, float green, float blue,float alpha){
	r=red;
	g=green;
	b=blue;
	a=alpha;
}

float
Color::R() const{
	return r;
}

float
Color::G() const{
	return g;
}

float
Color::B() const{
	return b;
}

}
