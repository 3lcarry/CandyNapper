#include "glwidget.h"
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#elif _WIN32
	#include <Windows.h>
	#include <gl\GL.h>
	#include <gl\GLU.h>
	#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <QMessageBox>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>

using namespace std;

int idEnemy=1;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));    
    timer.start(16);
    pintar=false;
}

void GLWidget::initializeGL(){
    glClearColor(0,0,0,1);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(-ancho/2,-alto/2,-ancho-20);
        glVertex3f(ancho/2,-alto/2,-ancho-20);
        glVertex3f(ancho/2,alto/2,-ancho-20);
        glVertex3f(-ancho/2,alto/2,-ancho-20);
    glEnd();        

    pintarPersonaje();
    pintarEnemigos();
    pintarObstaculos();
    pintarPared();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    gluPerspective(55, (float)w/h, 0.01, 5000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
}

void GLWidget::setAncho(float ac){
    ancho=ac;
}

void GLWidget::setAlto(float a){
    alto=a;
}

void GLWidget::setPersonaje(float x, float y,bool pintar){
    personaje.setX(x);
    personaje.setY(y);
    this->pintar=pintar;
}

void GLWidget::setEnemigo(float x, float y, int type){
    Enemy e;
    e.setCoords(x,y);
    e.setType(type);
    e.setId(idEnemy);
    idEnemy++;

    enemigos.push_back(e);
}

void GLWidget::setObstaculo(float x, float y, int type){
    Obstacle o;
    o.setCoords(x,y);
    o.setType(type);

    obstaculos.push_back(o);
}

void GLWidget::setPared(float x, float y, float xmax, float ymax){
    Point p;
    Point t;
    p.setX(x);
    p.setY(y);
    t.setX(xmax);
    t.setY(ymax);
    vector<Point> pared;
    pared.push_back(p);
    pared.push_back(t);

    paredes.push_back(pared);
}

void GLWidget::pintarPersonaje(){

    if(pintar){
        float segmentos=16.0;
        float incremento=2*M_PI/segmentos;
        float angulo =45.0/ 180 * M_PI;

        glColor3f(0.0,0.0,1.0);
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_TRIANGLE_FAN);
        for(int i=0; i<segmentos; i++){
                float x=personaje.getX()+2*cos(angulo);
                float y=personaje.getY()+2*sin(angulo);
                glVertex3f(x,y,-ancho-19.0);
                angulo+=incremento;
        }
        glEnd();
        glDisable(GL_BLEND);
    }
}

void GLWidget::pintarEnemigos(){

    if(enemigos.size()>0){
        for(int j=0; j<enemigos.size(); j++){
            float segmentos=16.0;
            float incremento=2*M_PI/segmentos;
            float angulo =45.0/ 180 * M_PI;

            glColor3f(1.0,0.0,0.0);
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin(GL_TRIANGLE_FAN);
            for(int i=0; i<segmentos; i++){
                    float x=enemigos[j].getX()+2*cos(angulo);
                    float y=enemigos[j].getY()+2*sin(angulo);
                    glVertex3f(x,y,-ancho-19.0);
                    angulo+=incremento;
            }
            glEnd();
            glDisable(GL_BLEND);
        }
    }

}

void GLWidget::pintarObstaculos(){

    if(obstaculos.size()>0){
        for(int j=0; j<obstaculos.size(); j++){
            float segmentos=4.0;
            float incremento=2*M_PI/segmentos;
            float angulo =45.0/ 180 * M_PI;

            glColor3f(0.0,0.0,0.0);
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin(GL_TRIANGLE_FAN);
            for(int i=0; i<segmentos; i++){
                    float x=obstaculos[j].getX()+2*cos(angulo);
                    float y=obstaculos[j].getY()+2*sin(angulo);
                    glVertex3f(x,y,-ancho-19.0);
                    angulo+=incremento;
            }
            glEnd();
            glDisable(GL_BLEND);
        }
    }
}

void GLWidget::pintarPared(){

    if(paredes.size()>0){
        for(int j=0; j<paredes.size(); j++){

            glColor3f(0.0,0.0,0.0);
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin(GL_QUADS);
                glVertex3f(paredes[j][0].getX()-paredes[j][1].getX(),paredes[j][0].getY()-paredes[j][1].getY(),-ancho-20.0);
                glVertex3f(paredes[j][0].getX()+paredes[j][1].getX(),paredes[j][0].getY()-paredes[j][1].getY(),-ancho-20.0);
                glVertex3f(paredes[j][0].getX()+paredes[j][1].getX(),paredes[j][0].getY()+paredes[j][1].getY(),-ancho-20.0);
                glVertex3f(paredes[j][0].getX()-paredes[j][1].getX(),paredes[j][0].getY()+paredes[j][1].getY(),-ancho-20.0);
            glEnd();
            glDisable(GL_BLEND);
        }
    }
}

void GLWidget::guardar(){

        ofstream fout;
        string nombre="xmlcn.xml";
        fout.open(nombre.c_str(),ios::out);

        if(fout.is_open()){

            fout<<"<CandyNapper>"<<endl;
            fout<<"     <Map "<<"x=\""<<alto<<"\" y=\""<<ancho<<"\">"<<"</Map>"<<endl;
            fout<<"     <Player "<<"x=\""<<personaje.getX()<<"\" y=\""<<personaje.getY()<<"\">"<<"</Player>"<<endl;
            fout<<"     <Enemies>"<<endl;
            for(int i=0; i<enemigos.size(); i++){                
                fout<<"         <Enemy "<<"x=\""<<enemigos[i].getX()<<"\" y=\""<<enemigos[i].getY()<<"\" type=\"";
                fout<<enemigos[i].getType()+1<<"\">"<<"</Enemy>"<<endl;
            }
            fout<<"     </Enemies>"<<endl;
            fout<<"     <Obstacles>"<<endl;
            for(int i=0; i<obstaculos.size(); i++){                
                fout<<"         <Obstacles "<<"x=\""<<obstaculos[i].getX()<<"\" y=\""<<obstaculos[i].getY()<<"\" type=\"";
                fout<<obstaculos[i].getType()+1<<"\">"<<"</Obstacles>"<<endl;
            }
            fout<<"     </Obstacles>"<<endl;
            fout<<"     <Walls>"<<endl;
            for(int j=0; j<paredes.size(); j++){                
                fout<<"       <Wall>"<<endl;
                fout<<"         <Coords x=\""<<paredes[j][0].getX()-paredes[j][1].getX()<<"\" y=\""<<paredes[j][0].getY()-paredes[j][1].getY()<<"\"></Coords>"<<endl;
                fout<<"         <Coords x=\""<<paredes[j][0].getX()-paredes[j][1].getX()<<"\" y=\""<<paredes[j][0].getY()+paredes[j][1].getY()<<"\"></Coords>"<<endl;
                fout<<"         <Coords x=\""<<paredes[j][0].getX()+paredes[j][1].getX()<<"\" y=\""<<paredes[j][0].getY()+paredes[j][1].getY()<<"\"></Coords>"<<endl;
                fout<<"         <Coords x=\""<<paredes[j][0].getX()+paredes[j][1].getX()<<"\" y=\""<<paredes[j][0].getY()-paredes[j][1].getY()<<"\"></Coords>"<<endl;
                fout<<"       </Wall>"<<endl;
            }
            fout<<"     </Walls>"<<endl;
            fout<<"</CandyNapper>"<<endl;

            QMessageBox msgBox;
             msgBox.setText("Mapa Guardado con Exito");
             msgBox.exec();

            fout.close();
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("El fichero no se ha podido abrir");
            msgBox.exec();
        }
}

