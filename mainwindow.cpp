#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/fasttransforms.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _signalWnd = new cGraphWindow(this);
    _patternWnd = new cGraphWindow(this);
    _resultWnd = new cGraphWindow(this);
    _signalIsLoaded = false;
    _patternIsLoaded = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbLoadSignal_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, tr("Загрузить файл сигнала"), QCoreApplication::applicationDirPath(), "*.txt Файл сигнала;;*.* Все файлы");
    if (str == "") return;

    QFile fileSignal(str);
    if(!fileSignal.open(QIODevice::ReadOnly)) {
        return;
    }
    _signalWnd->clearPlot();
    QByteArray bytes=fileSignal.readAll();
    str = QString(bytes);
    QStringList strList = str.split("\r\n");
    int i;
    foreach(QString s, strList) {
        _signalWnd->addValue(s.toDouble());
        if(i < LENGTH_OF_SIGNAL) _signalArr[i++] = s.toDouble();
    }
    ui->lSignalLoaded->setText("СИГНАЛ ЗАГРУЖЕН");
    _signalIsLoaded = true;
    _signalWnd->show();
}

void MainWindow::on_pbLoadPattern_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, tr("Загрузить файл паттерна"), QCoreApplication::applicationDirPath(), "*.txt Файл паттерна;;*.* Все файлы");
    if (str == "") return;

    QFile filePattern(str);
    if(!filePattern.open(QIODevice::ReadOnly)) {
        return;
    }
    _patternWnd->clearPlot();
    QByteArray bytes=filePattern.readAll();
    str = QString(bytes);
    QStringList strList = str.split("\r\n");
    int i;
    foreach(QString s, strList) {
        _patternWnd->addValue(s.toDouble());
        if(i < LENGTH_OF_PATTERN) _patternArr[i++] = s.toDouble();
    }
    ui->lPatternLoaded->setText("ПАТТЕРН ЗАГРУЖЕН");
    _patternIsLoaded = true;
    _patternWnd->show();
}

void MainWindow::on_pbCalc_clicked()
{
    if (_patternIsLoaded && _signalIsLoaded) {
        alglib::real_1d_array s, p, result;
        s.setcontent(LENGTH_OF_SIGNAL, _signalArr);
        p.setcontent(LENGTH_OF_PATTERN, _patternArr);
        result.setcontent(LENGTH_OF_SIGNAL+LENGTH_OF_PATTERN, _resultArr);
        alglib::corrr1d(s, LENGTH_OF_SIGNAL, p, LENGTH_OF_PATTERN, result);
        for(int i; i < result.length(); i++) {
            _resultWnd->addValue(result[i]);
        }
        _resultWnd->show();
    };
}
