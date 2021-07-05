HEADERS += \
           $$PWD/gradientwidget.h \
           $$PWD/node_p.h \
           $$PWD/toolstrip_p.h

SOURCES += \
           $$PWD/gradientwidget.cpp

win32 {
    HEADERS +=
    SOURCES +=
}

mac {
    HEADERS += $$PWD/macstyle.h
    SOURCES += $$PWD/macstyle.cpp
}
