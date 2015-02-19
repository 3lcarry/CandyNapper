#include "candyeditor.h"
#include "ui_candyeditor.h"
#include <QMessageBox>

CandyEditor::CandyEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CandyEditor)
{    
    ui->setupUi(this);
    ui->gbElementos->setHidden(true); //mantiene el grup box de los elementos escondido
}

CandyEditor::~CandyEditor()
{
    delete ui;
}

void CandyEditor::on_btCrearMapa_2_clicked()
{
    if(ui->tbAlto_2->text()!="" && ui->tbAncho_2->text()!=""){
        alto = ui->tbAlto_2->text().toFloat();
        ancho = ui->tbAncho_2->text().toFloat();
        if(alto>=500 && ancho>=500){
            ui->widget->setAncho(ancho);
            ui->widget->setAlto(alto);            
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("El minimo del mapa debe ser de 500x500");
            msgBox.exec();
        }
    }
}

void CandyEditor::on_btPersonaje_clicked()
{
    if(ui->tbPerX->text()!="" && ui->tbPerY->text()!=""){

        if(ui->tbPerX->text().toFloat()<=ancho/2.0 && ui->tbPerY->text().toFloat()<=alto/2.0){
            ui->widget->setPersonaje(ui->tbPerX->text().toFloat(),ui->tbPerY->text().toFloat(),true);
            ui->gbElementos->setHidden(false);
            ui->gbCrearMapa->setHidden(true);
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("El personaje no se puede colocar fuera de las coordenadas del mapa");
            msgBox.exec();
        }
    }
}

void CandyEditor::on_btEnemigo_clicked()
{
    if(ui->tbEneX->text()!="" && ui->tbEneY->text()!=""){

        if(ui->tbEneX->text().toFloat()<=ancho/2.0 && ui->tbEneY->text().toFloat()<=alto/2.0){
            ui->widget->setEnemigo(ui->tbEneX->text().toFloat(),
                                   ui->tbEneY->text().toFloat(),
                                   ui->cbEnemigos->currentIndex());
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("El enemigo no se puede colocar fuera de las coordenadas del mapa");
            msgBox.exec();
        }
    }
}

void CandyEditor::on_btObstaculo_clicked()
{
    if(ui->tbObsX->text()!="" && ui->tbObsY->text()!=""){

        if(ui->tbObsX->text().toFloat()<=ancho/2.0 && ui->tbObsY->text().toFloat()<=alto/2.0){
            ui->widget->setObstaculo(ui->tbObsX->text().toFloat(),
                                     ui->tbObsY->text().toFloat(),
                                     ui->cbObstaculos->currentIndex());
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("El obstaculo no se puede colocar fuera de las coordenadas del mapa");
            msgBox.exec();
        }        
    }
}


void CandyEditor::on_btPared_clicked()
{
    if(ui->tbParedX->text()!="" && ui->tbParedY->text()!="" && ui->tbParedX_2->text()!="" && ui->tbParedY_2->text()!=""){

        if(ui->tbParedX->text().toFloat()<=ancho/2.0 && ui->tbParedY->text().toFloat()<=alto/2.0){
            ui->widget->setPared(ui->tbParedX->text().toFloat(), ui->tbParedY->text().toFloat(),
                                 ui->tbParedX_2->text().toFloat(), ui->tbParedY_2->text().toFloat());
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("La pared no se puede colocar fuera de las coordenadas del mapa");
            msgBox.exec();
        }
    }
}

void CandyEditor::on_btGuardar_clicked()
{
    ui->widget->guardar();
}
