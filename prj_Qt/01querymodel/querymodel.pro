HEADERS       = ../connection.h \
                customsqlmodel.h \
                dbase.h \
                editablesqlmodel.h
SOURCES       = customsqlmodel.cpp \
                dbase.cpp \
                editablesqlmodel.cpp \
                main.cpp
QT           += sql widgets
requires(qtConfig(tableview))

# install
target.path = $$[QT_INSTALL_EXAMPLES]/sql/querymodel
INSTALLS += target

