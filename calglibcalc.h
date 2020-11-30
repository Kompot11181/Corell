#ifndef CALGLIBCALC_H
#define CALGLIBCALC_H

#include <QObject>
#include <QVector>
#include "src/fasttransforms.h"

// класс для работы с библиотекой AlgLib
class cAlglibCalc : public QObject
{
    Q_OBJECT
public:
    explicit cAlglibCalc(QObject *parent = 0);

signals:
    void calculated(QString name, QVector<double>& result);

public slots:
    void calcCorrr1D(const QVector<double> &signal, const QVector<double> &pattern);    // функция кросскорелляции

private:
    QVector <double> _result;       // результат вычислений
    double          _max;           // максимальное значение
    int             _index;         // индекс максимального значения
};

#endif // CALGLIBCALC_H
