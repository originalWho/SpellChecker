#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T15:56:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpellCheck
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hashtable.cpp \
    filehelper.cpp \
    texthelper.cpp

HEADERS  += mainwindow.h \
    filehelper.h \
    texthelper.h \
    hashtable.h

FORMS    += mainwindow.ui
