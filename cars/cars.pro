#-------------------------------------------------
#
# Project created by QtCreator 2015-11-15T17:10:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = cars
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    road.cpp \
    car.cpp \
    squareobj.cpp \
    traffic.cpp \
    trafficlight.cpp

HEADERS  += mainwindow.h \
    road.h \
    car.h \
    squareobj.h \
    traffic.h \
    trafficlight.h

FORMS    += mainwindow.ui
