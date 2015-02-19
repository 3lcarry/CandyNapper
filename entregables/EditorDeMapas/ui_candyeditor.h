/********************************************************************************
** Form generated from reading UI file 'candyeditor.ui'
**
** Created: Tue Mar 20 09:16:04 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANDYEDITOR_H
#define UI_CANDYEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_CandyEditor
{
public:
    QWidget *centralWidget;
    QPushButton *btGuardar;
    QPushButton *btSalir;
    GLWidget *widget;
    QGroupBox *gbCrearMapa;
    QLineEdit *tbAncho_2;
    QPushButton *btCrearMapa_2;
    QLineEdit *tbAlto_2;
    QPushButton *btPersonaje;
    QLineEdit *tbPerX;
    QLineEdit *tbPerY;
    QGroupBox *gbElementos;
    QPushButton *btEnemigo;
    QPushButton *btObstaculo;
    QLineEdit *tbEneX;
    QLineEdit *tbEneY;
    QLineEdit *tbObsY;
    QLineEdit *tbObsX;
    QLineEdit *tbParedY;
    QPushButton *btPared;
    QLineEdit *tbParedX;
    QLineEdit *tbParedY_2;
    QLineEdit *tbParedX_2;
    QComboBox *cbEnemigos;
    QComboBox *cbObstaculos;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CandyEditor)
    {
        if (CandyEditor->objectName().isEmpty())
            CandyEditor->setObjectName(QString::fromUtf8("CandyEditor"));
        CandyEditor->resize(845, 557);
        centralWidget = new QWidget(CandyEditor);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btGuardar = new QPushButton(centralWidget);
        btGuardar->setObjectName(QString::fromUtf8("btGuardar"));
        btGuardar->setGeometry(QRect(10, 470, 97, 27));
        btSalir = new QPushButton(centralWidget);
        btSalir->setObjectName(QString::fromUtf8("btSalir"));
        btSalir->setGeometry(QRect(110, 470, 97, 27));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setEnabled(true);
        widget->setGeometry(QRect(219, 9, 611, 481));
        gbCrearMapa = new QGroupBox(centralWidget);
        gbCrearMapa->setObjectName(QString::fromUtf8("gbCrearMapa"));
        gbCrearMapa->setEnabled(true);
        gbCrearMapa->setGeometry(QRect(20, 10, 181, 221));
        gbCrearMapa->setTitle(QString::fromUtf8("Crear Mapa"));
        gbCrearMapa->setCheckable(false);
        tbAncho_2 = new QLineEdit(gbCrearMapa);
        tbAncho_2->setObjectName(QString::fromUtf8("tbAncho_2"));
        tbAncho_2->setGeometry(QRect(0, 30, 71, 27));
        btCrearMapa_2 = new QPushButton(gbCrearMapa);
        btCrearMapa_2->setObjectName(QString::fromUtf8("btCrearMapa_2"));
        btCrearMapa_2->setGeometry(QRect(0, 70, 97, 27));
        tbAlto_2 = new QLineEdit(gbCrearMapa);
        tbAlto_2->setObjectName(QString::fromUtf8("tbAlto_2"));
        tbAlto_2->setGeometry(QRect(100, 30, 71, 27));
        btPersonaje = new QPushButton(gbCrearMapa);
        btPersonaje->setObjectName(QString::fromUtf8("btPersonaje"));
        btPersonaje->setGeometry(QRect(10, 160, 151, 31));
        tbPerX = new QLineEdit(gbCrearMapa);
        tbPerX->setObjectName(QString::fromUtf8("tbPerX"));
        tbPerX->setGeometry(QRect(0, 120, 71, 27));
        tbPerY = new QLineEdit(gbCrearMapa);
        tbPerY->setObjectName(QString::fromUtf8("tbPerY"));
        tbPerY->setGeometry(QRect(100, 120, 71, 27));
        gbElementos = new QGroupBox(centralWidget);
        gbElementos->setObjectName(QString::fromUtf8("gbElementos"));
        gbElementos->setEnabled(true);
        gbElementos->setGeometry(QRect(20, 10, 161, 421));
        btEnemigo = new QPushButton(gbElementos);
        btEnemigo->setObjectName(QString::fromUtf8("btEnemigo"));
        btEnemigo->setGeometry(QRect(10, 130, 141, 27));
        btObstaculo = new QPushButton(gbElementos);
        btObstaculo->setObjectName(QString::fromUtf8("btObstaculo"));
        btObstaculo->setGeometry(QRect(10, 260, 141, 27));
        tbEneX = new QLineEdit(gbElementos);
        tbEneX->setObjectName(QString::fromUtf8("tbEneX"));
        tbEneX->setGeometry(QRect(10, 40, 61, 27));
        tbEneY = new QLineEdit(gbElementos);
        tbEneY->setObjectName(QString::fromUtf8("tbEneY"));
        tbEneY->setGeometry(QRect(90, 40, 61, 27));
        tbObsY = new QLineEdit(gbElementos);
        tbObsY->setObjectName(QString::fromUtf8("tbObsY"));
        tbObsY->setGeometry(QRect(90, 170, 61, 27));
        tbObsX = new QLineEdit(gbElementos);
        tbObsX->setObjectName(QString::fromUtf8("tbObsX"));
        tbObsX->setGeometry(QRect(10, 170, 61, 27));
        tbParedY = new QLineEdit(gbElementos);
        tbParedY->setObjectName(QString::fromUtf8("tbParedY"));
        tbParedY->setGeometry(QRect(90, 310, 61, 27));
        btPared = new QPushButton(gbElementos);
        btPared->setObjectName(QString::fromUtf8("btPared"));
        btPared->setGeometry(QRect(10, 390, 141, 27));
        tbParedX = new QLineEdit(gbElementos);
        tbParedX->setObjectName(QString::fromUtf8("tbParedX"));
        tbParedX->setGeometry(QRect(10, 310, 61, 27));
        tbParedY_2 = new QLineEdit(gbElementos);
        tbParedY_2->setObjectName(QString::fromUtf8("tbParedY_2"));
        tbParedY_2->setGeometry(QRect(90, 350, 61, 27));
        tbParedX_2 = new QLineEdit(gbElementos);
        tbParedX_2->setObjectName(QString::fromUtf8("tbParedX_2"));
        tbParedX_2->setGeometry(QRect(10, 350, 61, 27));
        cbEnemigos = new QComboBox(gbElementos);
        cbEnemigos->setObjectName(QString::fromUtf8("cbEnemigos"));
        cbEnemigos->setGeometry(QRect(10, 90, 141, 27));
        cbEnemigos->setMinimumContentsLength(5);
        cbObstaculos = new QComboBox(gbElementos);
        cbObstaculos->setObjectName(QString::fromUtf8("cbObstaculos"));
        cbObstaculos->setGeometry(QRect(10, 220, 141, 27));
        cbObstaculos->setMinimumContentsLength(5);
        CandyEditor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CandyEditor);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 845, 25));
        CandyEditor->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CandyEditor);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CandyEditor->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CandyEditor);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CandyEditor->setStatusBar(statusBar);

        retranslateUi(CandyEditor);
        QObject::connect(btSalir, SIGNAL(clicked()), CandyEditor, SLOT(close()));

        cbEnemigos->setCurrentIndex(0);
        cbObstaculos->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CandyEditor);
    } // setupUi

    void retranslateUi(QMainWindow *CandyEditor)
    {
        CandyEditor->setWindowTitle(QApplication::translate("CandyEditor", "CandyEditor", 0, QApplication::UnicodeUTF8));
        btGuardar->setText(QApplication::translate("CandyEditor", "Guardar", 0, QApplication::UnicodeUTF8));
        btSalir->setText(QApplication::translate("CandyEditor", "Salir", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        gbCrearMapa->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        gbCrearMapa->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        tbAncho_2->setText(QString());
        tbAncho_2->setPlaceholderText(QApplication::translate("CandyEditor", "Ancho", 0, QApplication::UnicodeUTF8));
        btCrearMapa_2->setText(QApplication::translate("CandyEditor", "Crear", 0, QApplication::UnicodeUTF8));
        tbAlto_2->setText(QString());
        tbAlto_2->setPlaceholderText(QApplication::translate("CandyEditor", "Alto", 0, QApplication::UnicodeUTF8));
        btPersonaje->setText(QApplication::translate("CandyEditor", "A\303\261adir Personaje", 0, QApplication::UnicodeUTF8));
        tbPerX->setPlaceholderText(QApplication::translate("CandyEditor", "X", 0, QApplication::UnicodeUTF8));
        tbPerY->setPlaceholderText(QApplication::translate("CandyEditor", "Y", 0, QApplication::UnicodeUTF8));
        gbElementos->setTitle(QApplication::translate("CandyEditor", "Elementos", 0, QApplication::UnicodeUTF8));
        btEnemigo->setText(QApplication::translate("CandyEditor", "A\303\261adir Enemigo", 0, QApplication::UnicodeUTF8));
        btObstaculo->setText(QApplication::translate("CandyEditor", "A\303\261adir Obstaculo", 0, QApplication::UnicodeUTF8));
        tbEneX->setPlaceholderText(QApplication::translate("CandyEditor", "X", 0, QApplication::UnicodeUTF8));
        tbEneY->setPlaceholderText(QApplication::translate("CandyEditor", "Y", 0, QApplication::UnicodeUTF8));
        tbObsY->setPlaceholderText(QApplication::translate("CandyEditor", "Y", 0, QApplication::UnicodeUTF8));
        tbObsX->setPlaceholderText(QApplication::translate("CandyEditor", "X", 0, QApplication::UnicodeUTF8));
        tbParedY->setPlaceholderText(QApplication::translate("CandyEditor", "Y", 0, QApplication::UnicodeUTF8));
        btPared->setText(QApplication::translate("CandyEditor", "A\303\261adir Pared", 0, QApplication::UnicodeUTF8));
        tbParedX->setPlaceholderText(QApplication::translate("CandyEditor", "X", 0, QApplication::UnicodeUTF8));
        tbParedY_2->setPlaceholderText(QApplication::translate("CandyEditor", "Y max", 0, QApplication::UnicodeUTF8));
        tbParedX_2->setPlaceholderText(QApplication::translate("CandyEditor", "X max", 0, QApplication::UnicodeUTF8));
        cbEnemigos->clear();
        cbEnemigos->insertItems(0, QStringList()
         << QApplication::translate("CandyEditor", "Tipo 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CandyEditor", "Tipo 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CandyEditor", "Tipo 3", 0, QApplication::UnicodeUTF8)
        );
        cbObstaculos->clear();
        cbObstaculos->insertItems(0, QStringList()
         << QApplication::translate("CandyEditor", "Tipo 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CandyEditor", "Tipo 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CandyEditor", "Tipo 3", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class CandyEditor: public Ui_CandyEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANDYEDITOR_H
