QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab3
TEMPLATE = app

RESOURCES += \
    ../res.qrc

FORMS += \
    ../widget.ui

HEADERS += \
    ../widget.h

SOURCES += \
    ../main.cpp \
    ../widget.cpp
