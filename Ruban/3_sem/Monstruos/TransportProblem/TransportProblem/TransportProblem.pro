TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    volumeandcost.cpp \
    planningmatrix.cpp \
    container.cpp \
    potential.cpp

HEADERS += \
    volumeandcost.h \
    planningmatrix.h \
    container.h \
    potential.h
