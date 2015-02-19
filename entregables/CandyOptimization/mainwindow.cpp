#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SimplexSolver.h"
#include <sstream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clearLayout(ui->glRest);
    ui->frResultado->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearLayout(QGridLayout* gl)
{
    while(gl->count() > 0) {
        QWidget* widget = gl->itemAt(0)->widget();
        gl->removeWidget(widget);
        delete widget;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msAux; //Para DEBUG
    QString qsAux;
    string sFuncObjetivo;
    string sAux;
    int iNumRest;
    int iMetodo;

    //Variables del simplex
    vector<string> vsProbl;
    candy::SimplexSolver ss;
    candy::Rational optimo;
    vector<candy::Rational> soluciones;

    //Oculto el frResultado
    ui->frResultado->setVisible(false);

    //Leo los campos del formulario
    //Leo la funcion objetivo
    qsAux = ui->cbTipoFuncion->currentText() + " " + ui->leFuncObjetivo->text();
    sFuncObjetivo = qsAux.toStdString();
    vsProbl.push_back(sFuncObjetivo);

    //Leo las restricciones
    iNumRest = ui->leNumRest->text().toInt();
    for(int i = 0; i < iNumRest; i++){
        qsAux = _vectorRestr[i]->text();
        sAux = qsAux.toStdString();
        vsProbl.push_back(sAux);
    }

    //Construyo el problema
    candy::Problema pProbl(vsProbl);

    //Leo el metodo
    iMetodo = ui->cbMetodo->currentIndex();
    switch(iMetodo){
        case 0:
                //Simplex
                ss.SimplexSolve(pProbl);
                break;
        case 1:
                //Penalizaciones
                ss.PenalizacionesSolve(pProbl);
                break;
        case 2:
                //Dual
                ss.DualSimplexSolve(pProbl);
                break;

        case 3:
                //Enteros
                ss.IntSimplexSolve(pProbl);
                break;
    }

    optimo = ss.getOptimoFinal();
    soluciones = ss.getSoluciones();

    //Al final...
    ostringstream ossProblema;
    ossProblema << pProbl;
    ostringstream ossOptimo;
    ossOptimo << optimo;

    ui->leProblema->setText(QString::fromStdString(ossProblema.str()));
    if(ss.getEstado() == candy::SimplexSolver::SolEncontrada){
        ui->lbNoResultado->setVisible(false);
        ui->frOptimo->setVisible(false);
        clearLayout(ui->glVariables);

        ui->leOptimo->setText(QString::fromStdString(ossOptimo.str()));
        for(int i = 0; i < soluciones.size(); i++){
            ostringstream aux;
            aux << soluciones[i];

            QLineEdit* le = new QLineEdit(QString::fromStdString(aux.str()));
            le->setAlignment(Qt::AlignHCenter);
            le->setReadOnly(true);
            QLabel* lb = new QLabel("X" + QString::number(i + 1));
            lb->setAlignment(Qt::AlignCenter);

            ui->glVariables->addWidget(lb, 0, i);
            ui->glVariables->addWidget(le, 1, i);
        }
        ui->frOptimo->setVisible(true);
    }else{
        ui->lbNoResultado->setVisible(true);
        ui->frOptimo->setVisible(false);
    }

    ui->frResultado->setVisible(true);
}

void MainWindow::on_leNumRest_textChanged(const QString &arg1)
{
    clearLayout(ui->glRest);
    _vectorRestr.clear();
    int numRest = ui->leNumRest->text().toInt();
    for(int i = 0; i < numRest; i++){
        //Creo las cosas
        QLineEdit* le = new QLineEdit();
        le->setFixedWidth(326);
        le->setFixedHeight(22);
        QString numero = QString::number(i + 1);
        QLabel* lb = new QLabel(numero);
        _vectorRestr.push_back(le);

        //Añado el label
        ui->glRest->addWidget(lb, i, 0);
        //Añado el line edit
        ui->glRest->addWidget(le, i, 1);
    }
}
