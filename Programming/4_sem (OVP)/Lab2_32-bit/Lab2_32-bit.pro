greaterThan(QT_MAJOR_VERSION, 4): QT += core gui widgets
CONFIG += qt

MAJOR_VERSION = 1
MINOR_VERSION = 0
DEFINES += \
        MAJOR_VERSION=$$MAJOR_VERSION \
        MINOR_VERSION=$$MINOR_VERSION \
        QT_DEPRECATED_WARNINGS

FORMS += \
    ../Lab2/mainwindow.ui

HEADERS += \
    ../Lab2/mainwindow.h \
    ../Lab2/eventhandlingview.h

SOURCES += \
    ../Lab2/main.cpp \
    ../Lab2/mainwindow.cpp \
    ../Lab2/eventhandlingview.cpp

RESOURCES += ../resources/resources.qrc
