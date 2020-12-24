#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/fasttransforms.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGUI();
    qRegisterMetaType <VectorDouble>();
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
    ui->progressBar->setVisible(false);
}

// поменять местами f(t) и g(t)
void MainWindow::on_pbSwap_clicked()
{
    QString tempStr = "";
    VectorDouble tempVal;
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

void MainWindow::on_pbFtoR_clicked()
{
    VectorDouble _result = _f->getPoints();
    if(_result.size() == 0) return;
    QString name = "-f(t)";
    double mid = 0.0;               // поиск среднего значения
    foreach(double v, _result) {
        mid += v;
    }
    mid /= _result.size();
    QString tempStr = "";
    cGraphWindow * graph;
    if(ui->cbGraph->checkState() == Qt::Checked) graph = new cGraphWindow(this);
    double max = 0.0; int index = 0;
    for(int i = 0; i < _result.size(); i++) {
        _result[i] = -_result[i];   //2*mid -_result[i];
        if(ui->cbGraph->checkState() == Qt::Checked) graph->addValue(_result[i]);
        tempStr = (tempStr == "") ? QString("%1").arg(_result[i]) : QString("%1; %2").arg(tempStr).arg(_result[i]);
        if (max < _result[i]) {max = _result[i]; index = i;}
    }
    ui->teResult->setPlainText(tempStr);
    if(ui->cbGraph->checkState() == Qt::Checked) {
        graph->changeTitle(QString("Результат вычисления %1").arg(name));
        graph->changeHeader(QString("%1. Всего точек: %2. макс = %3 (# %4)").arg(name).arg(_result.size()).arg(max).arg(index));
        graph->show();
    }
}

void MainWindow::on_pbGtoR_clicked()
{
    VectorDouble _result = _g->getPoints();
    if(_result.size() == 0) return;
    QString name = "-g(t)";
    double mid = 0.0;               // поиск среднего значения
    foreach(double v, _result) {
        mid += v;
    }
    mid /= _result.size();
    QString tempStr = "";
    cGraphWindow * graph;
    if(ui->cbGraph->checkState() == Qt::Checked) graph = new cGraphWindow(this);
    double max = 0.0; int index = 0;
    for(int i = 0; i < _result.size(); i++) {
        _result[i] = -_result[i];   //2*mid -_result[i];
        if(ui->cbGraph->checkState() == Qt::Checked) graph->addValue(_result[i]);
        tempStr = (tempStr == "") ? QString("%1").arg(_result[i]) : QString("%1; %2").arg(tempStr).arg(_result[i]);
        if (max < _result[i]) {max = _result[i]; index = i;}
    }
    ui->teResult->setPlainText(tempStr);
    if(ui->cbGraph->checkState() == Qt::Checked) {
        graph->changeTitle(QString("Результат вычисления %1").arg(name));
        graph->changeHeader(QString("%1. Всего точек: %2. макс = %3 (# %4)").arg(name).arg(_result.size()).arg(max).arg(index));
        graph->show();
    }
}

void MainWindow::on_pbRevF_clicked()
{
    VectorDouble _result = _f->getPoints();
    if(_result.size() == 0) return;
    QString name = "f(-t)";
    QString tempStr = "";
    cGraphWindow * graph;
    if(ui->cbGraph->checkState() == Qt::Checked) graph = new cGraphWindow(this);
    double max = 0.0; int index = 0;
    for(int i = _result.size() - 1; i >= 0; i--) {
        if(ui->cbGraph->checkState() == Qt::Checked) graph->addValue(_result[i]);
        tempStr = (tempStr == "") ? QString("%1").arg(_result[i]) : QString("%1; %2").arg(tempStr).arg(_result[i]);
        if (max < _result[i]) {max = _result[i]; index = _result.size() -1 - i;}
    }
    ui->teResult->setPlainText(tempStr);
    if(ui->cbGraph->checkState() == Qt::Checked) {
        graph->changeTitle(QString("Результат вычисления %1").arg(name));
        graph->changeHeader(QString("%1. Всего точек: %2. макс = %3 (# %4)").arg(name).arg(_result.size()).arg(max).arg(index));
        graph->show();
    }
}

void MainWindow::on_pbRevG_clicked()
{
    VectorDouble _result = _g->getPoints();
    if(_result.size() == 0) return;
    QString name = "g(-t)";
    QString tempStr = "";
    cGraphWindow * graph;
    if(ui->cbGraph->checkState() == Qt::Checked) graph = new cGraphWindow(this);
    double max = 0.0; int index = 0;
    for(int i = _result.size() - 1; i >= 0; i--) {
        if(ui->cbGraph->checkState() == Qt::Checked) graph->addValue(_result[i]);
        tempStr = (tempStr == "") ? QString("%1").arg(_result[i]) : QString("%1; %2").arg(tempStr).arg(_result[i]);
        if (max < _result[i]) {max = _result[i]; index = _result.size() -1 - i;}
    }
    ui->teResult->setPlainText(tempStr);
    if(ui->cbGraph->checkState() == Qt::Checked) {
        graph->changeTitle(QString("Результат вычисления %1").arg(name));
        graph->changeHeader(QString("%1. Всего точек: %2. макс = %3 (# %4)").arg(name).arg(_result.size()).arg(max).arg(index));
        graph->show();
    }
}

void MainWindow::on_pbMuliFG_clicked()
{
    VectorDouble f = _f->getPoints();
    VectorDouble g = _g->getPoints();
    if ((f.size() ==0) || (g.size()==0)) return;
    QString name = "f(t)*g(t)";
    QString tempStr = "";
    cGraphWindow * graph;
    if(ui->cbGraph->checkState() == Qt::Checked) graph = new cGraphWindow(this);
    double max = 0.0; int index = 0;
    int len = (f.size() > g.size()) ? f.size() : g.size();
    int f_ptr = 0, g_ptr = 0;
    double v = 0.0;
    for (int i = 0; i < len; i++) {
        if(f_ptr >= f.size()) f_ptr = 0;
        if(g_ptr >= g.size()) g_ptr = 0;
        v = f[f_ptr++] * g[g_ptr++];
        if(ui->cbGraph->checkState() == Qt::Checked) graph->addValue(v);
        if (max < v) {max = v; index = i;}
        tempStr = (tempStr == "") ? QString("%1").arg(v) : QString("%1; %2").arg(tempStr).arg(v);
    }
    ui->teResult->setPlainText(tempStr);
    if(ui->cbGraph->checkState() == Qt::Checked) {
        graph->changeTitle(QString("Результат вычисления %1").arg(name));
        graph->changeHeader(QString("%1. Всего точек: %2. макс = %3 (# %4)").arg(name).arg(len).arg(max).arg(index));
        graph->show();
    }
}

// прочитать результат преобразования
void MainWindow::calculated(QString name, VectorDouble result)
{
    int msec = time.elapsed();
    if(result.size()) {
        cGraphWindow * graph;
        if(ui->cbGraph->checkState() == Qt::Checked) graph = new cGraphWindow(this);
        double max = 0.0; int i = 0, index = 0;
        QString tempStr = "";
        ui->progressBar->setVisible(true);
        ui->progressBar->setMaximum(result.size());
        foreach (auto v, result) {
            ui->progressBar->setValue(i);
            if(ui->cbGraph->checkState() == Qt::Checked) graph->addValue(v);
            if (max < v) {max = v; index = i;}
            tempStr = (tempStr == "") ? QString("%1").arg(v) : QString("%1; %2").arg(tempStr).arg(v);
            ++i;
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        ui->teResult->setPlainText(tempStr);
        ui->progressBar->setVisible(false);
        if(ui->cbGraph->checkState() == Qt::Checked) {
            graph->changeTitle(QString("Результат вычисления %1").arg(name));
            graph->changeHeader(QString("%1. Всего точек: %2. макс = %3 (# %4)").arg(name).arg(result.size()).arg(max).arg(index));
            graph->show();
        }
    }
    thread.terminate();
    calc->disconnect();
    calc->deleteLater();
    qDebug() << "Time from" << name << "elapsed:" << msec << "ms.";
}

// включить функцию рассчёта кросс-корелляции
void MainWindow::on_pbCorr_clicked()
{
    calc = new cAlglibCalc(0);
    connect(&thread, SIGNAL(started()), calc, SLOT(calcCorrr1D()));
    connect(calc, SIGNAL(calculated(QString, VectorDouble)), this, SLOT(calculated(QString, VectorDouble)));
    calc->moveToSignal(_f->getPoints());
    calc->moveToPattern(_g->getPoints());
    calc->moveToThread(&thread);
    time.restart();
    thread.start();
}

// включить функцию рассчёта замкнутой кросс-корелляции
void MainWindow::on_pbCorrCirc_clicked()
{
    calc = new cAlglibCalc(0);
    connect(&thread, SIGNAL(started()), calc, SLOT(calcCorrr1DCircular()));
    connect(calc, SIGNAL(calculated(QString, VectorDouble)), this, SLOT(calculated(QString, VectorDouble)));
    calc->moveToSignal(_f->getPoints());
    calc->moveToPattern(_g->getPoints());
    calc->moveToThread(&thread);
    time.restart();
    thread.start();
}

// включить функцию кубической интерполяции
void MainWindow::on_pbInterCube_clicked()
{
    calc = new cAlglibCalc(0);
    connect(&thread, SIGNAL(started()), calc, SLOT(calcSplineCube()));
    connect(calc, SIGNAL(calculated(QString, VectorDouble)), this, SLOT(calculated(QString, VectorDouble)));
    calc->moveToSignal(_f->getPoints());
    calc->moveToPattern(VectorDouble());
    calc->moveToThread(&thread);
    time.restart();
    thread.start();
}

// включить функцию монотонной интерполяции
void MainWindow::on_pbInterMono_clicked()
{
    calc = new cAlglibCalc(0);
    connect(&thread, SIGNAL(started()), calc, SLOT(calcSplineMono()));
    connect(calc, SIGNAL(calculated(QString, VectorDouble)), this, SLOT(calculated(QString, VectorDouble)));
    calc->moveToSignal(_f->getPoints());
    calc->moveToPattern(VectorDouble());
    calc->moveToThread(&thread);
    time.restart();
    thread.start();
}


// включить функцию прямого преобразования Фурье
void MainWindow::on_pbFFT_clicked()
{
    calc = new cAlglibCalc(0);
    connect(&thread, SIGNAL(started()), calc, SLOT(calcFFT()));
    connect(calc, SIGNAL(calculated(QString, VectorDouble)), this, SLOT(calculated(QString, VectorDouble)));
    calc->moveToSignal(_f->getPoints());
    calc->moveToPattern(VectorDouble());
    calc->moveToThread(&thread);
    time.restart();
    thread.start();
}

// включить функцию обратного преобразования Фурье
void MainWindow::on_pbIFFT_clicked()
{
    calc = new cAlglibCalc(0);
    connect(&thread, SIGNAL(started()), calc, SLOT(calcIFFT()));
    connect(calc, SIGNAL(calculated(QString, VectorDouble)), this, SLOT(calculated(QString, VectorDouble)));
    calc->moveToSignal(_f->getPoints());
    calc->moveToPattern(VectorDouble());
    calc->moveToThread(&thread);
    time.restart();
    thread.start();
}

void MainWindow::on_pbSave_clicked()
{

}
