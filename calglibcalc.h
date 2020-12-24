#ifndef CALGLIBCALC_H
#define CALGLIBCALC_H

#include <QObject>
#include "vectordouble.h"
#include "src/fasttransforms.h"
#include "src/interpolation.h"

// класс для работы с библиотекой AlgLib
class cAlglibCalc : public QObject
{
    Q_OBJECT
public:
    explicit cAlglibCalc(QObject *parent = 0);
    void moveToSignal(const VectorDouble signal) {_signal = signal;}
    void moveToPattern(const VectorDouble pattern) {_pattern = pattern;}

signals:
    void calculated(QString name, VectorDouble result);

public slots:
    void calcSplineCube();          // функция кубической интерполяции
    void calcSplineMono();          // функция монотонной интерполяции
    void calcFFT();                 // функция преобразования Фурье
    void calcIFFT();                // функция обратного преобразования Фурье
    void calcCorrr1D();             // функция кросскорелляции
    void calcCorrr1DCircular();     // функция кросскорелляции замкнутая

private:
    VectorDouble _signal;           // сигнал для обработки
    VectorDouble _pattern;          // паттерн для поиска внутри сигнала
    VectorDouble _result;           // результат вычислений
    double          _max;           // максимальное значение
    int             _index;         // индекс максимального значения
};

#endif // CALGLIBCALC_H
