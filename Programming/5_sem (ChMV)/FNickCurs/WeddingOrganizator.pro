#-------------------------------------------------
#
# Project created by QtCreator 2017-12-12T12:49:13
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeddingOrganizator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    database.h

FORMS    += mainwindow.ui

RESOURCES += \
    ../resources/resources.qrc
