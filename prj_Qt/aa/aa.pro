#-------------------------------------------------
# Project created by Murat BALCI 2018-03-05T12:00:50
#-------------------------------------------------

# Modules controlled by DEFINES
#DEFINES += LINUX
DEFINES	+= CUSTOM_MODEL
DEFINES += MAIN
DEFINES += ADRS
#DEFINES += HSAP
#DEFINES += OTHR

DEFINES += LINUX

DISTFILES += aaaprogram.txt \
    renk.qss


# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui sql widgets

TARGET = aa
TEMPLATE = app
CONFIG  += C++latest

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0



contains(DEFINES, MAIN) {

SOURCES +=       \
    main/cm_dlg_cb_htur.cpp \
    main/cm_dlg_richtxt.cpp \
    main/cm_treexml.cpp \
main/main.cpp    \
main/cw_hkk.cpp  \
main/dbase.cpp   \
main/taskitem.cpp          \
libs/alt_key.cpp \
libs/aqp.cpp     \
libs/hc_.cpp     \
libs/kuhn_munkres.cpp \
libs/tamamla.cpp \
libs/VTKontrol.cpp

#main/mw_main.cpp \
#main/login.cpp   \
HEADERS  +=    \
    main/cm_dlg_cb_htur.h \
    main/cm_dlg_richtxt.h \
    main/cm_treexml.h \
main/cw_hkk.h  \
main/dbase.h   \
main/taskitem.h          \
libs/VTKontTekkere.h \
libs/VTKontrol.h \
libs/VTTekton.h  \
libs/alt_key.h   \
libs/aqp.h     \
libs/globals.h \
libs/hc_.h     \
libs/kuhn_munkres.h \
libs/tamamla.h

#main/mw_main.h \
 #FORMS    += \
#main/login.h   \
}
contains(DEFINES, ADRS) {

SOURCES +=    \
adrs/clsn.cpp \
adrs/frm.cpp  \
adrs/ftr.cpp

HEADERS  +=  \
adrs/clsn.h  \
adrs/frm.h   \
adrs/ftr.h

 #FORMS    += \

}

contains(DEFINES, HSAP) {

SOURCES +=                   \
hsap/hc_hspdetay.cpp

HEADERS  +=                \
hsap/hc_hspdetay.h

}

contains(DEFINES, OTHR) {

SOURCES +=       \
    mchn/mkn.cpp \
    mchn/mkn_cinsi.cpp  \
    mchn/mkn_marka.cpp  \
    mchn/mkn_modeli.cpp \ 
    mlzm/mlzm.cpp    \
    mlzm/mlzm_gc.cpp \
    ie/ie.cpp    \
    ie/iedet.cpp \
    ie/tsnr.cpp  \
    ie/sclk.cpp  \
    grph/sortingbox.cpp \
    grph/shapeitem.cpp


HEADERS  +=    \
    mchn/mkn.h \
    mchn/mkn_cinsi.h  \
    mchn/mkn_marka.h  \
    mchn/mkn_modeli.h \
    mlzm/mlzm.h    \
    mlzm/mlzm_gc.h \
    ie/ie.h    \
    ie/iedet.h \
    ie/tsnr.h  \
    ie/sclk.h  \
    grph/sortingbox.h \
    grph/shapeitem.h

 #FORMS    += \

}

FORMS    +=     \
    wd_login.ui \
    cw_hkk.ui  \
    mn_navi.ui \
    login.ui   \
    dbase.ui


RESOURCES += \
    src.qrc

 #RESOURCES += \
   # hesap/main/timelog.qrc \
#    hesap/timelog.qrc \
 #   hsap/timelog.qrc \
  #  libs/aqp.qrc \
  #  src.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \libs

DISTFILES += \ libs/mime.types
   # hesap/main/images/0.png \
   # hesap/main/images/1.png \
   #hesap/main/images/2.png \
   # hesap/main/images/3.png \
   # hesap/main/images/4.png \
   # hesap/main/images/editadd.png \
   # hesap/main/images/editcut.png \
   # hesap/main/images/editdelete.png \
   # hesap/main/images/editdemote.png \
   # hesap/main/images/editdown.png \
   # hesap/main/images/editpaste.png \
   # hesap/main/images/editpromote.png \
   # hesap/main/images/editup.png \
   # hesap/main/images/filenew.png \
   # hesap/main/images/fileopen.png \
   # hesap/main/images/filequit.png \
   # hesap/main/images/filesave.png \
    # hesap/main/images/icon.png

HEADERS += \
    hsap/hc_hspadd.h \
    main/cm_dlg_le_richtxt.h \
    main/cw_dlg_options.h \
    main/dialog.h \
    hsap/proxymodel.h \
    hsap/uniqueproxymodel.h \
    hsap/uniqueproxymodel.h \
    main/hc_hesaptree.h \
    main/hesapturu.h \
    main/main.h \
    main/mainwindow.h

SOURCES += \
    hsap/hc_hspadd.cpp \
    main/cm_dlg_le_richtxt.cpp \
    main/cw_dlg_options.cpp \
    main/dialog.cpp \
    hsap/proxymodel.cpp \
    hsap/uniqueproxymodel.cpp \
    main/hc_hesaptree.cpp \
    main/hesapturu.cpp \
    main/login.cpp \
    main/mainwindow.cpp

# kısaltmalar
# cm - class model
# cw - class widget
# cb - combobox
# dlg - dialog
# dlG - delegate
# le - lineedit


