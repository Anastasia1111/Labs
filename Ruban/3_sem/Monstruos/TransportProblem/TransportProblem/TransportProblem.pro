TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    volumeandcost.cpp \
    ../../FracClass/frac.cpp \
    planningmatrix.cpp \
    container.cpp

HEADERS += \
    volumeandcost.h \
    ../../FracClass/frac.h \
    planningmatrix.h \
    container.h
