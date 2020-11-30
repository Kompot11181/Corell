#ifndef CFUNCTION_H
#define CFUNCTION_H

#include <QtWidgets>
#include "cgraphwindow.h"
//#include "qcustomplot.h"


namespace Ui {
class cFunction;
}

class cFunction : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString _name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit cFunction(QWidget *parent = 0);
    cFunction(QString _name, QWidget *parent = 0);
    ~cFunction();

    QString name() const {return _name;}
    void setName(const QString name);
    QVector<double> getPoints() const;

signals:
    void nameChanged(QString name);

public slots:
    void changePoints(QString str);

private slots:
    void on_pbLoad_clicked();
    void on_pbGraph_clicked();

private:
    Ui::cFunction *ui;
    QString _name;      // название функцииж
};

#endif // CFUNCTION_H
