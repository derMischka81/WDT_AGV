#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T14:39:02
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtDIO
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    QLabelClick.cpp

HEADERS += mainwindow.h \
    QLabelClick.h

FORMS += mainwindow.ui

RESOURCES += QtDIO.qrc

unix: LIBS += -L/usr/lib -lwdt_dio
