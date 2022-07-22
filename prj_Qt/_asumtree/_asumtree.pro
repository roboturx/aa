
QT += widgets sql

CONFIG	    += console debug


DEFINES	    += CUSTOM_MODEL

HEADERS	    += \
    main/defines.h \
    main/hc_hsp.h \
    main/richtextlineedit.hpp \
    main/richtextdelegate.hpp \
    main/taskitem.hpp \
    main/treemodel.hpp \
    lib/globals.h \
    lib/aqp/kuhn_munkres.hpp \
    lib/aqp/alt_key.hpp \
    lib/aqp/aqp.hpp

SOURCES	    += main/main.cpp \
    lib/aqp/mainx.cpp \
    main/hc_hsp.cpp \
    main/taskitem.cpp \
    main/treemodel.cpp \
    main/richtextlineedit.cpp \
    main/richtextdelegate.cpp \
    lib/aqp/kuhn_munkres.cpp \
    lib/aqp/alt_key.cpp \
    lib/aqp/aqp.cpp


RESOURCES   += main/timelog.qrc \
    lib/aqp/aqp.qrc

SUBDIRS += \
    lib/aqp/aqp.pro

DISTFILES += \
    lib/aqp/mime.types

INCLUDEPATH += main \
    lib \
    lib/aqp \

win32 { INCLUDEPATH += . }

debug {
    exists(../modeltest-0.2/modeltest.pri) {
	DEFINES	    += MODEL_TEST
	include(../modeltest-0.2/modeltest.pri)
    }
}

