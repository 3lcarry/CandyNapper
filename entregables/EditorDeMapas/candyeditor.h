#ifndef CANDYEDITOR_H
#define CANDYEDITOR_H

#include <QMainWindow>

namespace Ui {
    class CandyEditor;
}

class CandyEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit CandyEditor(QWidget *parent = 0);
    ~CandyEditor();

private slots:        

    void on_btCrearMapa_2_clicked();

    void on_btPersonaje_clicked();

    void on_btEnemigo_clicked();

    void on_btObstaculo_clicked();    

    void on_btPared_clicked();

    void on_btGuardar_clicked();

private:
    Ui::CandyEditor *ui;
    float ancho;
    float alto;
};

#endif // CANDYEDITOR_H
