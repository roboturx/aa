#-------------------------------------------------
#
# Project created by QtCreator 2018-03-05T12:00:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aa
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    cw_mkn.cpp \
    ww_mkcins.cpp \
    cw_per.cpp \
    cw_grs.cpp \
    cw_isemri.cpp \
    mkevrk.cpp \
    dlgt_mkstok.cpp \
    cw_gelir.cpp \
    VTKontrol.cpp \
    cw_hkk.cpp \
    hc_tableview.cpp \
    mw_main.cpp \
    wd_dptlp.cpp \
    cw_fr.cpp \
    tamamla.cpp \
    cw_ambar.cpp \
    mknnn.cpp \
    form.cpp \
    cw_ftr.cpp \
    login.cpp

HEADERS  += \
    globals.h \
    cw_mkn.h \
    ww_mkcins.h \
    dlgt_mkstok.h \
    cw_per.h \
    cw_grs.h \
    cw_isemri.h \
    mkevrk.h \
    cw_gelir.h \
    VTKontrol.h \
    VTKontTekkere.h \
    VTTekton.h \    
    cw_hkk.h \
    main.h \
    hc_tableview.h \
    mw_main.h \
    wd_dptlp.h \
    cw_fr.h \
    tamamla.h \
    cw_ambar.h \
    mknnn.h \
    form.h \
    cw_ftr.h \
    login.h

FORMS    += \
    wd_login.ui \
    ww_mkcins.ui \
    cw_hkk.ui \
    mn_navi.ui \
    cw_dpdet.ui \
    wd_dptlp.ui \
    cw_fr.ui \
    cw_tasinir.ui \
    form.ui \
    cw_.ui \
    login.ui \
    dlg_ambar.ui

CONFIG  += C++11

RESOURCES += \
    src.qrc

