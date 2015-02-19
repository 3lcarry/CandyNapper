#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <vector>
#include <QGridLayout>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_leNumRest_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void clearLayout(QGridLayout* gl);
    vector<QLineEdit*> _vectorRestr;
};

#endif // MAINWINDOW_H
