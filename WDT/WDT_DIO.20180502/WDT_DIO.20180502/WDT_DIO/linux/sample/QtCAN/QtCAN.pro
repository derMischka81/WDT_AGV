#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T16:46:30
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCAN
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui

RESOURCES += QtCAN.qrc

unix: LIBS += -L/usr/lib -lwdt_dio

