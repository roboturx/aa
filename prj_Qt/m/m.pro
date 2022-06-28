QT      += core gui
QT      += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
<<<<<<< HEAD
    task.cpp

HEADERS += \
    mainwindow.h \
    task.h
=======
    mytreemodel.cpp

HEADERS += \
    mainwindow.h \
    mytreemodel.h
>>>>>>> 66530a8afc8517249a02eaba32f7ca94a1d83505

FORMS += \
    mainwindow.ui \
    task.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
