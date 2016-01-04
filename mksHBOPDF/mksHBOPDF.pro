#-------------------------------------------------
#
# Project created by QtCreator 2015-12-22T14:48:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mksHBOPDF
TEMPLATE = app


CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    documentparser.cpp \
    tag.cpp \
    tagvalue.cpp

HEADERS  += mainwindow.h \
    documentparser.h \
    tag.h \
    tagvalue.h

FORMS    += mainwindow.ui
