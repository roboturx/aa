
QT       += core  gui printsupport
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += widgets

TARGET = Qt-barcode
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG  += C++11
#CONFIG   += console
#CONFIG   -= app_bundle



SOURCES += main.cpp \
    barcodeprinter.cpp \
    mainwindow.cpp \
    code128.cpp \
    code128item.cpp

HEADERS += \
    barcodeprinter.h \
    mainwindow.h \
    code128.h \
    code128item.h

FORMS += \
    mainwindow.ui \
    mainwindow.ui
