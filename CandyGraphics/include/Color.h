/*
 * Color.h
 *
 *  Created on: 22/11/2011
 *      Author: gustavo
 */

#ifndef COLOR_H_
#define COLOR_H_
namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */
	/**
	 * Clase Color que permite aplicarle color a una figura
	 */
	class Color{

	private:
		/**
		 * float que contiene la cantidad de rojo
		 */
		float r;
		/**
		 * float que contiene la cantidad de verde
		 */
		float g;
		/**
		 * float que contiene la cantidad de azul
		 */
		float b;
		/**
		 * float para el alpha
		 */
		float a;

	public:

		/**
		 * Constructor por defecto de la clase color
		 */
		Color();
		/**
		 * Constructor sobrecargado de la clase color
		 * @param red float que indica la cantidad de rojo a aplicar
		 * @param green float que indica la cantidad de verde a aplicar
		 * @param blue float que indica la cantidad de azul a aplicar
		 * @param alpha indica el alpha
		 */
		Color(float red, float green, float blue, float alpha = 1.0);

		/**
		 * Método que devuelve la tonalidad roja
		 * @return r float que contiene la cantidad de rojo
		 */
		float R() const;
		/**
		 * Método que devuelve la tonalidad verde
		 * @return g float que contiene la cantidad de verde
		 */
		float G() const;
		/**
		 * Método que devuelve la tonalidad de azul
		 * @return b float que contiene la cantidad de azul
		 */
		float B() const;

		/**
		 * Getter del alpha del color
		 * @return alpha
		 */
		inline float A() const {return a;};
		/**
		 * Añade el alpha al color
		 * @param alpha
		 */

		inline void setA(float alpha) {a = alpha;}

		/**
		 * Método que añade una cantidad de rojo
		 * @param red float que contiene la cantidad de rojo
		 */
		inline void setR(double red){r=red;};
		/**
		 * Método que añade una cantidad de verde
		 * @param green float que contiene la cantidad de verde
		 */
		inline void setG(double green){g=green;};
		/**
		 * Método que añade una cantidad de azul
		 * @param blue float que contiene una cantidad de azul
		 */
		inline void setB(double blue){b=blue;};

		/**
		 * Color azul
		 */
		static Color Blue;

		/**
		 * Color rojo
		 */
		static Color Red;

		/**
		 * Color verde
		 */
		static Color Green;

		/**
		 * Color amarillo
		 */
		static Color Yellow;

		/**
		 * Color magenta
		 */
		static Color Magenta;

		/**
		 * Color cyan
		 */
		static Color Cyan;

		/**
		 * Color naranja
		 */
		static Color Orange;

		/**
		 * Color purpura
		 */
		static Color Purple;

		/**
		 * Color marron
		 */
		static Color Brown;

		/**
		 * Color negro
		 */
		static Color Black;

		/**
		 * Color blanco
		 */
		static Color White;

	};
}

#endif /* COLOR_H_ */
