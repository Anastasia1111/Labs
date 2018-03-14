TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../FracClass/frac.cpp \
    fracmatrixsymplex.cpp \
    matrixlimitation.cpp

HEADERS += \
    ../FracClass/frac.h \
    fracmatrixsymplex.h \
    matrixlimitation.h
