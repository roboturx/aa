
QT += widgets sql

CONFIG	    += console debug

DEFINES	    += MAIN
DEFINES	    += CUSTOM_MODEL

DEFINES	    += ADRS
DEFINES	    += MLZM
DEFINES     += HSAP
#DEFINES	    += OTHER

HEADERS	    += main/mainwindow.hpp \
    main/defines.h \
    main/richtextlineedit.hpp \
    main/richtextdelegate.hpp \
    main/taskitem.hpp \
    main/treemodel.hpp \
    lib/globals.h \
    lib/hc_.h \
    lib/login.h \
    lib/tamamla.h \
    lib/dbase/VTKontTekkere.h \
    lib/dbase/VTKontrol.h \
    lib/dbase/VTTekton.h \
    lib/dbase/dbase.h \
    lib/aqp/kuhn_munkres.hpp \
    lib/aqp/alt_key.hpp \
    lib/aqp/aqp.hpp \
    moduls/adrs/clsn.h \
    moduls/adrs/frm.h \
    moduls/adrs/ftr.h \
    moduls/hsap/hc_hsp.h \
    moduls/hsap/hc_hspdty.h \
    moduls/mlzm/mlzm.h \
    moduls/mlzm/mlzm_gc.h
SOURCES	    += main/main.cpp \
    lib/aqp/mainx.cpp \
    main/mainwindow.cpp \
    main/taskitem.cpp \
    main/treemodel.cpp \
    main/richtextlineedit.cpp \
    main/richtextdelegate.cpp \
    lib/login.cpp \
    lib/hc_.cpp \
    lib/tamamla.cpp \
    lib/dbase/VTKontrol.cpp \
    lib/dbase/dbase.cpp \
    lib/aqp/kuhn_munkres.cpp \
    lib/aqp/alt_key.cpp \
    lib/aqp/aqp.cpp \
    moduls/adrs/clsn.cpp \
    moduls/adrs/frm.cpp \
    moduls/adrs/ftr.cpp \
    moduls/hsap/hc_hsp.cpp \
    moduls/hsap/hc_hspdty.cpp \
    moduls/mlzm/mlzm.cpp \
    moduls/mlzm/mlzm_gc.cpp

RESOURCES   += main/timelog.qrc \
    lib/aqp/aqp.qrc

SUBDIRS += \
    lib/aqp/aqp.pro

DISTFILES += \
    lib/aqp/mime.types


INCLUDEPATH += main \
    lib \
    lib/aqp \
    lib/dbase \
    moduls \
    moduls/adrs \
    moduls/mlzm \
    moduls/hsap



win32 { INCLUDEPATH += . }

debug {
    exists(../modeltest-0.2/modeltest.pri) {
	DEFINES	    += MODEL_TEST
	include(../modeltest-0.2/modeltest.pri)
    }
}

