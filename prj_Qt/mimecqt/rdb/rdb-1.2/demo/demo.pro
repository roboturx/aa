QT  += gui core sql widgets
TEMPLATE = app
TARGET = rdbdemo

HEADERS   += editdialog.h \
             mainwindow.h \
             models.h \
             tables.h

SOURCES   += editdialog.cpp \
             main.cpp \
             mainwindow.cpp \
             models.cpp \
             tables.cpp \

FORMS     += editdialog.ui \
             mainwindow.ui

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
