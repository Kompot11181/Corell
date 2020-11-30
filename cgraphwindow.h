#ifndef CGRAPHWINDOW_H
#define CGRAPHWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QWidget>
#include <QtWidgets>
#include "qcustomplot.h"

namespace Ui {
class cGraphWindow;
}

class cGraphWindow : public QDialog
{
    Q_OBJECT

public:
    explicit cGraphWindow(QWidget *parent = 0);
    ~cGraphWindow();

    void changeTitle(QString);         // изменить название окна
    void changeHeader(QString str);    // изменить значение заголовка

public slots:

    void addValue(double);
    void clearPlot() {}
private:
    Ui::cGraphWindow *ui;
    QCPGraph *_graphic;
    QCustomPlot *_plot;

    void createPlot();
};

#endif // CGRAPHWINDOW_H
