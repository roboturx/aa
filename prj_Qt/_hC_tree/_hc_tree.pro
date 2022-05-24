QT += widgets sql
#requires(qtConfig(treeview))

FORMS       =
HEADERS     = \
              dbase.h \
              hc_tree.h \
              mainwindow.h \
              treesqlitem.h \
              treesqlmodel.h
#RESOURCES   = editabletreemodel.qrc
SOURCES     = \
              dbase.cpp \
              hc_tree.cpp \
              main.cpp \
              mainwindow.cpp \
              treesqlitem.cpp \
              treesqlmodel.cpp

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
#INSTALLS += target
