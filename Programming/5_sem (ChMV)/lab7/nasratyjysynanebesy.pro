#-------------------------------------------------
#
# Project created by QtCreator 2017-11-07T10:44:32
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nasratyjysynanebesy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    domparser.cpp \
    saxparser.cpp

HEADERS  += mainwindow.h \
    domparser.h \
    saxparser.h

FORMS    += mainwindow.ui
