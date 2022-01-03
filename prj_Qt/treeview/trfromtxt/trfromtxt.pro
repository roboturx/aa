QT += widgets sql core
requires(qtConfig(treeview))

FORMS       = mainwindow.ui \
    database.ui
HEADERS     = mainwindow.h \
              database.h \
              treeitem.h \
              treemodel.h
RESOURCES   = \
    tr22.qrc
SOURCES     = mainwindow.cpp \
              database.cpp \
              treeitem.cpp \
              treemodel.cpp \
              main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
INSTALLS += target
