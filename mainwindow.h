#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cfunction.h"
#include "calglibcalc.h"

#define LENGTH_OF_SIGNAL 512
#define LENGTH_OF_PATTERN 128

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initGUI();
public slots:
    void calculated(QString name, QVector<double> &result);

private slots:
    void on_pbRToF_clicked();
    void on_pbRToG_clicked();
    void on_pbSwap_clicked();

    void on_pbCorr_clicked();

private:
    Ui::MainWindow *ui; // окно программы
    cFunction * _f;     // функиця _f(t)
    cFunction * _g;     // функиця _g(t)
    cAlglibCalc * calc; // указатель на экзепляр калькулятора
    QThread thread;     // отдельный поток для расчёта


};

#endif // MAINWINDOW_H
