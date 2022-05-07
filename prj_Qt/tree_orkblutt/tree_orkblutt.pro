QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbase.cpp \
    hc_treeitem.cpp \
    hc_treemodel.cpp \
    main.cpp \
    hc_tree.cpp \
    mysqlmodel.cpp

HEADERS += \
    dbase.h \
    hc_tree.h \
    hc_treeitem.h \
    hc_treemodel.h \
    mysqlmodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
