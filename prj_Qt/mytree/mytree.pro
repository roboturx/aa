TEMPLATE   = app
TARGET     = mytree
QT        += sql widgets

HEADERS   += editdialog.h \
             database.h \
             logger.h \
             mainwidget.h \
             mainwindow.h \
             mainwindowxxxx.h \
             models.h \
             tables.h

SOURCES   += editdialog.cpp \
             database.cpp \
             logger.cpp \
             main.cpp \
    mainwidget.cpp \
             mainwindow.cpp \
    mainwindowxxxx.cpp \
             models.cpp \
             tables.cpp \

FORMS     += editdialog.ui \
             mainwindow.ui \
             mainwindowxxxx.ui

RESOURCES += icons.qrc

include( rdbmy.pri )

#INCLUDEPATH += rdbmy/

win32-msvc* {
    QMAKE_CXXFLAGS += -Fd\$(IntDir)
    CONFIG         -= flat
}

!win32 | build_pass {
    MOC_DIR = tmp
    RCC_DIR = tmp
    UI_DIR  = tmp
    CONFIG( debug, debug|release ) {
        OBJECTS_DIR = tmp/debug
        DESTDIR = debug
    } else {
        OBJECTS_DIR = tmp/release
        DESTDIR = release
    }
}

DISTFILES += \
    rdbmy.pri

CONFIG += c++14
DEFINES += \
  QT_DEPRECATED_WARNINGS \
  QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
  QT_RESTRICTED_CAST_FROM_ASCII
