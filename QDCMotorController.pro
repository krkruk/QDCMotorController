#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T14:42:41
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = QDCMotorController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    QDCController/qdcmodel.cpp \
    serialport.cpp \
    QDCController/qdcwidget.cpp

HEADERS  += mainwindow.h \
    QDCController/qdcmodelinterface.h \
    QDCController/qdcmodel.h \
    serialport.h \
    QDCController/qdcwidget.h

FORMS    += mainwindow.ui \
    QDCController/qdcwidget.ui
