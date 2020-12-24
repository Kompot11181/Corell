#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cfunction.h"
#include "calglibcalc.h"
#include "vectordouble.h"

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
    void calculated(QString name, VectorDouble result);

private slots:
    void on_pbFtoR_clicked();
    void on_pbGtoR_clicked();

    void on_pbRevF_clicked();
    void on_pbRevG_clicked();
    void on_pbMuliFG_clicked();

    void on_pbSwap_clicked();

    void on_pbInterCube_clicked();
    void on_pbInterMono_clicked();
    void on_pbFFT_clicked();
    void on_pbIFFT_clicked();
    void on_pbCorr_clicked();
    void on_pbCorrCirc_clicked();

    void on_pbSave_clicked();

private:
    Ui::MainWindow *ui; // окно программы
    cFunction * _f;     // функиця _f(t)
    cFunction * _g;     // функиця _g(t)
    cAlglibCalc * calc; // указатель на экзепляр калькулятора
    QThread thread;     // отдельный поток для расчёта
    QTime time;         // время обработки функции

};

#endif // MAINWINDOW_H
