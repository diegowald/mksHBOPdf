#-------------------------------------------------
#
# Project created by QtCreator 2015-12-22T14:48:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mksHBOPDF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    documentparser.cpp

HEADERS  += mainwindow.h \
    documentparser.h

FORMS    += mainwindow.ui
