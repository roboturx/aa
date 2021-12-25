QT       += core gui sql widgets printsupport

INCLUDEPATH +=

#include( ./commands/commands.pri)
include(./data/data.pri)
#include( ./dialogs/dialogs.pri)
#include( ./models/models.pri)

#include( ./sqlite/sqlite.pri)

include( ./utils/utils.pri)
#include( ./views/views.pri)
#include( ./widgets/widgets.pri)
#include( ./xmlui/xmlui.pri)


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    application.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    sqltreemodel.cpp

HEADERS += \
    application.h \
    database.h \
    mainwindow.h \
    sqltreemodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/icons.qrc \
    resources/resources.qrc
