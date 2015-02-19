#ifndef WIZARDINTRO_H
#define WIZARDINTRO_H

#include <QWizardPage>

namespace Ui {
class WizardIntro;
}

class WizardIntro : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit WizardIntro(QWidget *parent = 0);
    ~WizardIntro();
    
private:
    Ui::WizardIntro *ui;
};

#endif // WIZARDINTRO_H
