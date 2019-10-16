#-------------------------------------------------
#
# Project created by QtCreator 2018-03-05T12:00:50
#
#-------------------------------------------------

QT       += core gui sql
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aa
TEMPLATE = app
CONFIG  += C++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    mkevrk.cpp \
    dlgt_mkstok.cpp \
    VTKontrol.cpp \
    cw_hkk.cpp \
    mw_main.cpp \
    wd_dptlp.cpp \
    tamamla.cpp \
    mknnn.cpp \
    login.cpp \
    dbase.cpp \
    shapeitem.cpp \
    mkn_cinsi.cpp \
    mkn_marka.cpp \
    mkn_modeli.cpp \
    hc_.cpp \
    clsn.cpp \
    frm.cpp \
    ftr.cpp \
    mkn.cpp \
    mlzm.cpp \
    iedet.cpp \
    tsnr.cpp \
    sclk.cpp \
    ie.cpp \
    mlzm_gc.cpp \
    sortingbox.cpp


HEADERS  += \
    globals.h \
    dlgt_mkstok.h \
    mkevrk.h \
    VTKontrol.h \
    VTKontTekkere.h \
    VTTekton.h \    
    cw_hkk.h \
    main.h \
    mw_main.h \
    wd_dptlp.h \
    tamamla.h \
    mknnn.h \
    login.h \
    dbase.h \
    shapeitem.h \
    mkn_cinsi.h \
    mkn_marka.h \
    mkn_modeli.h \
    hc_.h \
    clsn.h \
    frm.h \
    ftr.h \
    mkn.h \
    mlzm.h \
    iedet.h \
    tsnr.h \
    sclk.h \
    ie.h \
    mlzm_gc.h \
    sortingbox.h
    # cw_cns.h

FORMS    += \
    forms/mainForm.ui \
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
    dlg_ambar.ui \
    dbase.ui



RESOURCES += \
    src.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../fridgemagnets/fridgemagnets.pro