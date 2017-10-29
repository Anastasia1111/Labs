#-------------------------------------------------
#
# Project created by QtCreator 2017-10-24T12:12:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab6
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    crypter.cpp \
    dbwindow.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    crypter.h \
    dbwindow.h \
    database.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dbwindow.ui

RESOURCES += \
    ../resources/resources.qrc
