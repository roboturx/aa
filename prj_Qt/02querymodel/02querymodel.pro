HEADERS       = connection.h \
                connection.h \
                editablesqlmodel.h \
                mainwindow.h \
                myitemmodel.h
SOURCES       = editablesqlmodel.cpp \
                main.cpp \
                mainwindow.cpp \
                myitemmodel.cpp
QT           += sql widgets
requires(qtConfig(tableview))

# install
target.path = $$[QT_INSTALL_EXAMPLES]/sql/querymodel
INSTALLS += target

FORMS += \
    mainwindow.ui

