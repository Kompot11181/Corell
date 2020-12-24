#-------------------------------------------------
#
# Project created by QtCreator 2020-11-26T14:05:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

# строки для профилирования в gprof (подробнее см. https://www.pvsm.ru/qt-2/10777 )
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

TARGET = Corell
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    src/alglibinternal.cpp \
    src/alglibmisc.cpp \
    src/ap.cpp \
    src/dataanalysis.cpp \
    src/diffequations.cpp \
    src/fasttransforms.cpp \
    src/integration.cpp \
    src/interpolation.cpp \
    src/linalg.cpp \
    src/optimization.cpp \
    src/solvers.cpp \
    src/specialfunctions.cpp \
    src/statistics.cpp \
    qcustomplot.cpp \
    cgraphwindow.cpp \
    cfunction.cpp \
    calglibcalc.cpp

HEADERS  += mainwindow.h \
    src/alglibinternal.h \
    src/alglibmisc.h \
    src/ap.h \
    src/dataanalysis.h \
    src/diffequations.h \
    src/fasttransforms.h \
    src/integration.h \
    src/interpolation.h \
    src/linalg.h \
    src/optimization.h \
    src/solvers.h \
    src/specialfunctions.h \
    src/statistics.h \
    src/stdafx.h \
    qcustomplot.h \
    cgraphwindow.h \
    cfunction.h \
    calglibcalc.h \
    vectordouble.h

FORMS    += mainwindow.ui \
    cgraphwindow.ui \
    cfunction.ui

RESOURCES += \
    source.qrc
