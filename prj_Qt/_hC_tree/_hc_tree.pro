QT += widgets sql
requires(qtConfig(treeview))

FORMS       = mainwindow.ui
HEADERS     = mainwindow.h \
              dbase.h \
              hc_tree.h \
              treesqlitem.h \
              treesqlmodel.h
#RESOURCES   = editabletreemodel.qrc
SOURCES     = mainwindow.cpp \
              dbase.cpp \
              hc_tree.cpp \
              main.cpp \
              treesqlitem.cpp \
              treesqlmodel.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
INSTALLS += target
