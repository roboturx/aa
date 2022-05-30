QT -= gui
QT += sql

TEMPLATE = lib
DEFINES += GALLERYCORE_LIBRARY
TARGET = gallery-core
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    album.cpp \
    picture.cpp

HEADERS += \
    album.h \
    gallery-core_global.h \
    picture.h

# Default rules for deployment.

!isEmpty(target.path): INSTALLS += target
