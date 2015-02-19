#ifndef DATAENTER_H
#define DATAENTER_H

#include <QMainWindow>

namespace Ui {
class DataEnter;
}

class DataEnter : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DataEnter(QWidget *parent = 0);
    ~DataEnter();
    
private:
    Ui::DataEnter *ui;
};

#endif // DATAENTER_H
