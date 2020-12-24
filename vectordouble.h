#ifndef VECTORDOUBLE
#define VECTORDOUBLE

// необходим для регистрации передаваемого параметра этого вариантного типа в поток данных!
// в исполняемом файле, где вызов потока добавить строку:
// qRegisterMetaType <VectorDouble> ("VectorDouble");

#include <QVector>

typedef QVector<double> VectorDouble;
Q_DECLARE_METATYPE(VectorDouble);


#endif // VECTORDOUBLE

