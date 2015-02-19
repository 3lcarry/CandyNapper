#-------------------------------------------------
#
# Project created by QtCreator 2012-02-22T15:26:03
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = EditorDeMapas
TEMPLATE = app


SOURCES += main.cpp\
        candyeditor.cpp \    
    glwidget.cpp \
    Point.cpp \
    enemy.cpp \
    obstacle.cpp

HEADERS  += candyeditor.h \    
    glwidget.h \
    Point.h \
    enemy.h \
    obstacle.h

FORMS    += candyeditor.ui

LIBS += -framework GLUT -lobjc

OTHER_FILES +=
