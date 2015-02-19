#include "dataenter.h"
#include "ui_dataenter.h"

DataEnter::DataEnter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataEnter)
{
    ui->setupUi(this);
}

DataEnter::~DataEnter()
{
    delete ui;
}
