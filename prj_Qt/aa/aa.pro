#-------------------------------------------------
#
# Project created by QtCreator 2018-03-05T12:00:50
#
#-------------------------------------------------

QT       += core gui sql
#QT       += multimedia
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


SOURCES +=\
    main/main.cpp \
    main/VTKontrol.cpp \
    main/cw_hkk.cpp \
    main/mw_main.cpp \
    main/login.cpp \
    main/dbase.cpp \
#    mchn/cw_cns.cpp \
 #   mchn/dlgt_mkstok.cpp \
  #  mchn/mkevrk.cpp \
    mchn/mkn.cpp \
    mchn/mkn_cinsi.cpp \
    mchn/mkn_marka.cpp \
    mchn/mkn_modeli.cpp \
   # mchn/mknnn.cpp \
    adrs/clsn.cpp \
    adrs/frm.cpp \
    adrs/ftr.cpp \
    mlzm/mlzm.cpp \
    mlzm/mlzm_gc.cpp \
 #   mlzm/wd_dptlp.cpp \
   # adrs/ftr.cpp \
    ie/ie.cpp \
    ie/iedet.cpp \
    ie/tsnr.cpp \
    ie/sclk.cpp \
    grph/sortingbox.cpp \
    grph/shapeitem.cpp \
    libs/hc_.cpp \
    libs/tamamla.cpp


HEADERS  += \
 #   main/main.h \
    main/VTKontrol.h \
    main/cw_hkk.h \
    main/mw_main.h \
    main/login.h \
    main/dbase.h \
    main/VTKontTekkere.h \
    main/VTTekton.h \
    main/globals.h \
  #  mchn/cw_cns.h \
#    mchn/dlgt_mkstok.h \
#    mchn/mkevrk.h \
    mchn/mkn.h \
    mchn/mkn_cinsi.h \
    mchn/mkn_marka.h \
    mchn/mkn_modeli.h \
#    mchn/mknnn.h \
#    mchn/ww_makina.h \
    adrs/clsn.h \
    adrs/frm.h \
    adrs/ftr.h \
    mlzm/mlzm.h \
    mlzm/mlzm_gc.h \
#    mlzm/wd_dptlp.h \
    ie/ie.h \
    ie/iedet.h \
    ie/tsnr.h \
    ie/sclk.h \
    grph/sortingbox.h \
    grph/shapeitem.h \
    libs/hc_.h \
    libs/tamamla.h


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
