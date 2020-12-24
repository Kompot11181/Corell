#include "cfunction.h"
#include "ui_cfunction.h"

cFunction::cFunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cFunction)
{
    ui->setupUi(this);
}

cFunction::cFunction(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cFunction)

{
    ui->setupUi(this);
    setName(name);
}

cFunction::~cFunction()
{
    delete ui;
}

void cFunction::setName(const QString name)
{
    _name = name;
    ui->groupBox->setTitle(_name);
    emit nameChanged(_name);
}

// возвращает сфоркированный массив, преобразованный из текста
VectorDouble cFunction::getPoints() const
{
    VectorDouble result;
    QString str = ui->tePoints->document()->toPlainText();
    QString splitStr = ";";
    str.replace('\n', splitStr);        // при "crlf" символ \r куда-то пропадает при чтении, поэтому меняем только один символ
    str.replace(' ', splitStr);
    if ( (str.contains(',')) && (str.contains('.')) ) str.replace(',', splitStr);
    if ( str.contains(',') ) str.replace(',', ".");
    str.remove(QRegExp("[^\\d." + splitStr +"-+eE]"));             // удаляет всё кроме цифр, разделителя дефиса (минуса)
    QStringList strList = str.split(splitStr);
    bool ok;
    foreach(QString s, strList) {
            double d = s.toDouble(&ok);
            if (ok) result.push_back(d);
    }
    return result;
}

// загрузка текста
void cFunction::on_pbLoad_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, tr("Загрузить файл функции ") + _name, QCoreApplication::applicationDirPath(), "*.txt Файл сигнала;;*.* Все файлы");
    if (str == "") return;

    QFile fileSignal(str);
    if(!fileSignal.open(QIODevice::ReadOnly)) {
        return;
    }
    QByteArray bytes=fileSignal.readAll();
    str = QString(bytes);
    ui->tePoints->setPlainText(str);
}

// вывод графика на экран
void cFunction::on_pbGraph_clicked()
{
    cGraphWindow * graph = new cGraphWindow(this);
    int i = 0;
    auto pts = getPoints();
    foreach (auto v, pts) {
        graph->addValue(v);
        ++i;
    }
    graph->changeTitle(_name);
    graph->changeHeader(QString("%1. Всего точек: %2").arg(_name).arg(i));
    graph->show();
}

void cFunction::changePoints(QString str)
{
    ui->tePoints->setPlainText(str);
}
