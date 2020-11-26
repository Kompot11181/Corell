#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/fasttransforms.h"
#include "cgraphwindow.h"
#include "qcustomplot.h"

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

private slots:
    void on_pbLoadSignal_clicked();

    void on_pbLoadPattern_clicked();

    void on_pbCalc_clicked();

private:
    Ui::MainWindow *ui;                 // окно программы
    cGraphWindow * _signalWnd;          // окно вывода сигнала
    cGraphWindow * _patternWnd;         // окно вывода контролькного сигнала
    cGraphWindow * _resultWnd;          // окно результата
    bool    _signalIsLoaded;
    bool    _patternIsLoaded;
    double _signalArr[LENGTH_OF_SIGNAL];             //
    double _patternArr[LENGTH_OF_PATTERN];            //
    double _resultArr[LENGTH_OF_SIGNAL + LENGTH_OF_PATTERN];    //
};

#endif // MAINWINDOW_H
