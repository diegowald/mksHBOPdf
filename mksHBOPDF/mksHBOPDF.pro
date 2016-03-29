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


SOURCES += \
    ../3rdParty/quazip-code/quazip/quazip/qioapi.cpp \
    ../3rdParty/quazip-code/quazip/quazip/JlCompress.cpp \
    ../3rdParty/quazip-code/quazip/quazip/quaadler32.cpp \
    ../3rdParty/quazip-code/quazip/quazip/quacrc32.cpp \
    ../3rdParty/quazip-code/quazip/quazip/quagzipfile.cpp \
    ../3rdParty/quazip-code/quazip/quazip/quaziodevice.cpp \
    ../3rdParty/quazip-code/quazip/quazip/quazip.cpp \
    ../3rdParty/quazip-code/quazip/quazip/quazipdir.cpp \
    ../3rdParty/quazip-code/quazip/quazip/quazipfile.cpp \
    ../3rdParty/quazip-code/quazip/quazip/quazipfileinfo.cpp \
    ../3rdParty/quazip-code/quazip/quazip/quazipnewinfo.cpp \
    ../3rdParty/quazip-code/quazip/quazip/unzip.c \
    ../3rdParty/quazip-code/quazip/quazip/zip.c \
    main.cpp\
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
    templatedoc.cpp \
    templateprocessor.cpp \
    htmltemmplateprocessor.cpp \
    docxtemplateprocessor.cpp

HEADERS  += \
    ../3rdParty/quazip-code/quazip/quazip/crypt.h \
    ../3rdParty/quazip-code/quazip/quazip/ioapi.h \
    ../3rdParty/quazip-code/quazip/quazip/JlCompress.h \
    ../3rdParty/quazip-code/quazip/quazip/quaadler32.h \
    ../3rdParty/quazip-code/quazip/quazip/quachecksum32.h \
    ../3rdParty/quazip-code/quazip/quazip/quacrc32.h \
    ../3rdParty/quazip-code/quazip/quazip/quagzipfile.h \
    ../3rdParty/quazip-code/quazip/quazip/quaziodevice.h \
    ../3rdParty/quazip-code/quazip/quazip/quazipdir.h \
    ../3rdParty/quazip-code/quazip/quazip/quazipfile.h \
    ../3rdParty/quazip-code/quazip/quazip/quazipfileinfo.h \
    ../3rdParty/quazip-code/quazip/quazip/quazip_global.h \
    ../3rdParty/quazip-code/quazip/quazip/quazip.h \
    ../3rdParty/quazip-code/quazip/quazip/quazipnewinfo.h \
    ../3rdParty/quazip-code/quazip/quazip/unzip.h \
    ../3rdParty/quazip-code/quazip/quazip/zip.h \
    mainwindow.h \
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
    templatedoc.h \
    templateprocessor.h \
    htmltemmplateprocessor.h \
    docxtemplateprocessor.h

FORMS    += mainwindow.ui \
    dlgpolizas.ui \
    dlgeditpoliza.ui \
    dlgasegurados.ui \
    dlgeditasegurado.ui

!win32: LIBS += -lz

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../mksHBOPdf-bin/quazip/quazip/release/ -lquazip
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../mksHBOPdf-bin/quazip/quazip/debug/ -lquazip
#else:unix: LIBS += -L$$PWD/../../mksHBOPdf-bin/quazip/quazip/ -lquazip

#INCLUDEPATH += $$PWD/../../mksHBOPdf/3rdParty/quazip-code/quazip/quazip
#DEPENDPATH += $$PWD/../../mksHBOPdf/3rdParty/quazip-code/quazip/quazip
