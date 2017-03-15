greaterThan(QT_MAJOR_VERSION, 4): QT += core gui widgets
CONFIG += qt

MAJOR_VERSION = 2
MINOR_VERSION = 0
DEFINES += \
        MAJOR_VERSION=$$MAJOR_VERSION \
        MINOR_VERSION=$$MINOR_VERSION \
        QT_DEPRECATED_WARNINGS

FORMS += \
    ../Lab2/mainwindow.ui \
    ../Lab2/colordialog.ui

HEADERS += \
    ../Lab2/mainwindow.h \
    ../Lab2/paintscene.h \
    ../Lab2/colordialog.h

SOURCES += \
    ../Lab2/main.cpp \
    ../Lab2/mainwindow.cpp \
    ../Lab2/paintscene.cpp \
    ../Lab2/colordialog.cpp

RESOURCES += ../resources/resources.qrc
