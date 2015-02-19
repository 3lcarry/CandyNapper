#-------------------------------------------------
#
# Project created by QtCreator 2012-05-17T21:17:00
#
#-------------------------------------------------

QT       += core gui

TARGET = CandyOptimization
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/CandyMath/lib/release/ -lcandy-math
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/CandyMath/lib/debug/ -lcandy-math
else:symbian: LIBS += -lcandy-math
else:unix: LIBS += -L$$PWD/../../build/CandyMath/lib/ -lcandy-math

INCLUDEPATH += $$PWD/../../CandyMath/include
DEPENDPATH += $$PWD/../../CandyMath/include
