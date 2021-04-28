HEADERS += $$PWD/localsettings.h \
           $$PWD/query.h \
           $$PWD/updateevent.h \
            $$PWD/datamanager.h

SOURCES +=  $$PWD/datamanager.cpp \
            $$PWD/localsettings.cpp \
    $$PWD/query.cpp \
           $$PWD/updateevent.cpp

contains( QT_CONFIG, openssl ) |
contains( QT_CONFIG, openssl-linked ) |
contains( QT_CONFIG, ssl ) {
  #  HEADERS += data/certificatesstore.h
 #   SOURCES += data/certificatesstore.cpp
}
