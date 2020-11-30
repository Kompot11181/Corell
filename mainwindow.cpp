#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/fasttransforms.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGUI()
{
    _f = new cFunction("f(t)", this);
    _g = new cFunction("g(t)", this);
    QSplitter * splitFunc = new QSplitter(Qt::Horizontal, this);
    splitFunc->addWidget(_f);
    splitFunc->addWidget(_g);
    ui->wFunctions->layout()->addWidget(splitFunc);
    ui->menuBar->setVisible(false);
    ui->mainToolBar->setVisible(false);
    ui->statusBar->setVisible(false);
}

// копирование из строки результата в функцию f(t)
void MainWindow::on_pbRToF_clicked()
{
    _f->changePoints(ui->teResult->document()->toPlainText());
}

// копирование из строки результата в функцию g(t)
void MainWindow::on_pbRToG_clicked()
{
    _g->changePoints(ui->teResult->document()->toPlainText());
}

// поменять местами f(t) и g(t)
void MainWindow::on_pbSwap_clicked()
{
    QString tempStr = "";
    QVector <double> tempVal;
// копировать из f(t)
    tempVal = _f->getPoints();
    foreach (double v, tempVal) {
        tempStr = (tempStr == "") ? QString("%1").arg(v) : QString("%1; %2").arg(tempStr).arg(v);
    }
// копировать из g(t)
    tempVal = _g->getPoints();
    _g->changePoints(tempStr);
    tempStr = "";
    foreach (double v, tempVal) {
        tempStr = (tempStr == "") ? QString("%1").arg(v) : QString("%1; %2").arg(tempStr).arg(v);
    }
    _f->changePoints(tempStr);
}

// прочитать результат преобразования
void MainWindow::calculated(QString name, QVector<double> &result)
{
    QString tempStr = "";
    foreach (double v, result) {
        tempStr = (tempStr == "") ? QString("%1").arg(v) : QString("%1; %2").arg(tempStr).arg(v);
    }
    ui->teResult->setPlainText(tempStr);

    cGraphWindow * graph = new cGraphWindow(this);
    double max = 0.0; int i = 0, index = 0;
    foreach (auto v, result) {
        graph->addValue(v);
        if (max < v) {max = v; index = i;}
        ++i;
    }
    graph->changeTitle(QString("Результат вычисления %1").arg(name));
    graph->changeHeader(QString("%1. Всего точек: %2. макс = %3 (# %4)").arg(name).arg(result.size()).arg(max).arg(index));
    graph->show();
}

void MainWindow::on_pbCorr_clicked()
{
    calc = new cAlglibCalc(this);
    connect(calc, SIGNAL(calculated(QString,QVector<double>&)), this, SLOT(calculated(QString,QVector<double>&)));
    calc->calcCorrr1D(_f->getPoints(), _g->getPoints());
}
