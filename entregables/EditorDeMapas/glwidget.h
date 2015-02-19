#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <iostream>
#include <vector>
#include "enemy.h"
#include "obstacle.h"
using namespace std;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);


public slots:
    void setAlto(float a);
    void setAncho(float ac);
    void setPersonaje(float x, float y,bool pintar);
    void setEnemigo(float x, float y, int type);
    void setObstaculo(float x, float y, int type);
    void setPared(float x, float y, float xmax, float ymax);
    void pintarPersonaje();
    void pintarEnemigos();
    void pintarObstaculos();    
    void pintarPared();
    void guardar();

private:
    bool pintar;
    QTimer timer;
    float ancho;
    float alto;
    Point personaje;    
    vector<Enemy> enemigos;
    vector<Obstacle> obstaculos;
    vector<vector<Point> > paredes;
};

#endif // GLWIDGET_H
