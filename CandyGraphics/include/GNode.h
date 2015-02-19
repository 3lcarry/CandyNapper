/*
 * GTree.h
 *
 *  Created on: 06/02/2012
 *      Author: gustavo
 */

#ifndef GNODE_H_
#define GNODE_H_

#include <iostream>
#include <list>
#include "Color.h"
#include "CandyMath.h"

using namespace std;

namespace candy{

	class GTree;

	class Camera;
	class Director;
	class Transformation;
	class Light;
	class Model;
	class Shape;
	class Text;
	class Line;
	class Box;
	class Plane;
	class guiButton;
	class guiRButton;
	class guiGBox;
    class guiSlide;
    class AnimatedTransformation;
    class Particles;
        
    class GNode{

        friend class GTree;

    public:

        enum GNodeType{
             E_Transformation,
             E_Camera,
             E_Director,
             E_Light,
             E_Model,
             E_Polygon,
             E_Scene,
             E_Text,
             E_Line,
             E_Plane,
             E_Box,
             E_Button,
             E_RButton,
             E_GBox,
             E_Slide,
             E_Particula
        };

        GNode(GNodeType tipo);
        virtual ~GNode();
        GNode(const GNode& node);
        GNode& operator=(const GNode& node);
        virtual void Render(bool seleccion) = 0;

        Camera* addCamera(float near, float far, float aspectRatio, float fov);
        Camera* addCamera2D(float left, float right, float bottom, float top);
        Director* addDirector(Vector3 ojo, Vector3 direccion, Vector3 up);
        Transformation* addTransformation();
        AnimatedTransformation* addAnimatedTransformation();
        Light* addLight(Vector3 posicion, Vector3 ambiente, Vector3 difusa, Vector3 especular, int numLuz);
        Model* addModel(int idModelo, int textura);
        Shape* addShape(int numLados, Color color);
        Text* addText();
        Line* addLine(Vector3 punto_final, Color color, bool punteada);
        Line* addLine(Vector3 punto_inicial, Vector3 punto_final, Color color, bool punteada);
        Box* addBox();
        Box* addBox(int idFront, int idBack, int idTop, int idBottom, int idLeft, int idRight);
        Plane* addPlane();
        guiButton* addButton(float ancho, float alto, string texto);
        guiRButton* addRButton(string texto, bool check);
        guiGBox* addGBox(float alto, float ancho);
        guiSlide* addSlide(float min, float max, float freq);
        Particles* addParticles(int num=500);

        GNode* addGNode(GNode* nodo);
        bool isActive();
        void setActive(bool active);
        void setID(int id);
        int getID();
        void setDestroy(bool dest);
        bool isDestroy();

        void setLight(bool light);
        bool isLight();

		/**
		 * Indica si esta o no activado el depth-testing
		 * @return TRUE si esta activado
		 */
		bool isDepth();

		/**
		 * Setter del z-buffer
		 * @param depth TRUE si queremos activarlo (por defecto esta activado)
		 */
		void setDepth(bool depth);

		/**
		 * Elimina los hijos de un nodo
		 */
		void rmChilds();
    protected:

        list<GTree*> hijos;
        GNodeType tipo;
        bool activo;
        void RenderHijos(bool seleccion);
        void copiarDesde(const GNode& cop);
        int id;
        bool destroy;
        bool _light;

		/**
		 * Indica si esta activado o no el depth-testing
		 */
		bool _depth;
    };
}
#endif /* GNODE_H_ */
