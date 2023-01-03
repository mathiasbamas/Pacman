TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(../../mingl.pri)

SOURCES += \
        bgtext.cpp \
        main.cpp

HEADERS += \
    bgtext.h
