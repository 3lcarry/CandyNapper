#ifndef QGLWIDGET_H
#define QGLWIDGET_H

#include <QGlWidget>

class QGLWidget : public QGlWidget
{
    Q_OBJECT
public:
    explicit QGLWidget(QObject *parent = 0);

    initializeGL();

};

#endif // QGLWIDGET_H
