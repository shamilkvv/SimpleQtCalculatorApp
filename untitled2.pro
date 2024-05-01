TARGET=Communicate

TEMPLATE = app

CONFIG += console c++20

CONFIG -= app_bundle


SOURCES += \
    anvor.cpp \
    main.cpp


QT += widgets
QT += qml
QT += multimedia

HEADERS += \
    anvor.h
