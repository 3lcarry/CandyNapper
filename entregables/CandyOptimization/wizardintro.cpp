#include "wizardintro.h"
#include "ui_wizardintro.h"

WizardIntro::WizardIntro(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WizardIntro)
{
    ui->setupUi(this);
}

WizardIntro::~WizardIntro()
{
    delete ui;
}
