#-------------------------------------------------
#
# Project created by QtCreator 2015-12-22T14:48:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mksHBOPDF
TEMPLATE = app


CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    documentparser.cpp \
    tag.cpp \
    tagvalue.cpp \
    dbhandler.cpp \
    poliza.cpp \
    asegurado.cpp \
    dlgpolizas.cpp \
    dlgeditpoliza.cpp \
    dlgasegurados.cpp \
    dlgeditasegurado.cpp \
    suplemento.cpp \
    documenttemplate.cpp \
    templatedoc.cpp

HEADERS  += mainwindow.h \
    documentparser.h \
    tag.h \
    tagvalue.h \
    dbhandler.h \
    poliza.h \
    asegurado.h \
    dlgpolizas.h \
    dlgeditpoliza.h \
    dlgasegurados.h \
    dlgeditasegurado.h \
    suplemento.h \
    documenttemplate.h \
    templatedoc.h

FORMS    += mainwindow.ui \
    dlgpolizas.ui \
    dlgeditpoliza.ui \
    dlgasegurados.ui \
    dlgeditasegurado.ui
