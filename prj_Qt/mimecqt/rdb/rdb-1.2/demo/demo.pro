QT  += gui core sql widgets
TEMPLATE = app
TARGET = rdbdemo

HEADERS   += editdialog.h \
             database.h \
             mainwindow.h \
             models.h \
             mw.h \
             tables.h

SOURCES   += editdialog.cpp \
    database.cpp \
             main.cpp \
             mainwindow.cpp \
             models.cpp \
    mw.cpp \
             tables.cpp \

FORMS     += editdialog.ui \
             mainwindow.ui \
             mw.ui

RESOURCES += icons.qrc

include( ../rdb/rdb.pri )

INCLUDEPATH += ..

win32-msvc* {
    QMAKE_CXXFLAGS += -Fd\$(IntDir)
    CONFIG -= flat
}

!win32 | build_pass {
    MOC_DIR = ../tmp
    RCC_DIR = ../tmp
    UI_DIR = ../tmp
    CONFIG( debug, debug|release ) {
        OBJECTS_DIR = ../tmp/debug
        DESTDIR = ../debug
    } else {
        OBJECTS_DIR = ../tmp/release
        DESTDIR = ../release
    }
}

DISTFILES += \
    tables.qmodel
